import os
import sys
import time
import threading
import asyncore
import smtpd
import smtplib
import json
import pickle
import copy
import email


# Mail Outgoing Proxxy
class MailOutgoingProxy:
    def __init__(self):
        self.srv = "smtp.gmail.com"
        #self.prt = 465
        self.prt = 587    # or 465, but you have to create smtp.lib.SMTP_SSL

        #Outgoing server login
        self.account = "unknown"
        self.pwd = "unknown"

        try:
            acinfo = open("outsrv_login.txt")
            lines = acinfo.read().splitlines()
            self.account = lines[0]
            self.pwd = lines[1]
            acinfo.close()
        except:
            print "Please specify your outgoing server account/pwd in outsrv_login.txt"


    def send(self, fr, to, msg):
        try:
            print "Mail outgoing via: " + self.srv + "#" + str(self.prt)
            if self.prt == 587:
                outsrv = smtplib.SMTP(self.srv, self.prt)
            else:
                outsrv = smtp.lib.SMTP_SSL(self.srv, self.prt)

            outsrv.ehlo()   # ESMTP Identification
            outsrv.starttls() # Enable TLS Mode

            # Login Proxy SMTP Server, and sending.
            outsrv.login(self.account, self.pwd)
            outsrv.sendmail(fr, to, msg)

            outsrv.close()
            print "Mail outgoing account: " + self.account

        except:
            print "mail outgoing fail."


# Mail Database Factory, via python Pickle tools
class MailDatabase:
    def __init__(self, mailDBFile):
        self.dbFile = mailDBFile
        self.content = None

        if os.path.exists(self.dbFile):
            fd = open(self.dbFile,'r')
            try:
                self.content = pickle.load(fd)
            except:
                print "Invalid MailBox DB."

            fd.close()

    def read(self):
        return self.content

    def save(self, c):
        self.content = c;
        fd = open(self.dbFile,'w+')
        pickle.dump(self.content, fd)
        fd.close()


# Mail Server Handler
mailOutgoing = MailOutgoingProxy()
mailBox = MailDatabase('mailBox.db')
mailQueue = []

class MailServer(smtpd.SMTPServer):
    def process_message(self,_peer,_from,_to,_data):
        msg = {
            'from' : _from,
            'to' : _to,
            'data' : _data,
            'time' : time.time()
        }
        mailQueue.append(msg)
        self.store_message(msg)

        print ""
        print 'from', _from
        print 'to', _to
        print 'peer', _peer
        #print 'data', _data

        # Send outside mails through Proxy SMTP Server
        domainpos = _to[0].find('@') + 1
        maildomain = _to[0][domainpos : ]
        print "@mail domain: " + maildomain
        if maildomain != "localhost":
            mailOutgoing.send(_from, _to, _data)

    def store_message(self,msg):
        data = mailBox.read()
        if data is None:
            data = {}
        if not data.has_key('messages'):
            data['messages'] = []

        msg['id'] = len(data['messages']) + 1
        data['messages'].append(msg)
        mailBox.save(data)

class MailServerHandler(threading.Thread,object):
    def __init__(self, hostInfo):
        threading.Thread.__init__(self)
        self.hostInfo = hostInfo
        self.active = True
        self.server = None

    def run(self):
        while self.active:
            try:
                asyncore.loop()
            except:
                print 'MailHandler error'
            pass

        self.close()

    def close(self):
        asyncore.close_all()
        print 'Mail Server closes.'
        self.active = False

    def setup(self):
        print 'Mail Server starts.'
        self.start()
        self.server = MailServer(self.hostInfo, None)
        pass


# Bottle Template Render
from django.conf import settings
settings.configure(TEMPLATE_DIRS=("static",))

import django.template
import django.template.loader

def render(name, *values):
    ctx = django.template.Context()
    for d in values:
        ctx.push()
        ctx.update(d)

    t = django.template.loader.get_template(name)
    return str(t.render(ctx))


#
# MailBox Page
#
import bottle
from bottle import Bottle, route as bottlerun, static_file

MailBoxPage = Bottle()
mailCount = 0

@MailBoxPage.route('/static/<path>')
def serveStaticContent(path):
    return static_file(path, root="static")

@MailBoxPage.route('/api/has_new')
def hasNew():
    if len(mailQueue) > 0:
        return 'true'
    return 'false'

@MailBoxPage.route('/api/read/<id>')
def readMsg(id=-1):
    content = mailBox.read()
    messages = []

    try:
        id = int(id)
        messages = content['messages']
        msg = filter( lambda m: m['id'] == id, messages ).pop()

        if not msg.has_key('read') or msg['read'] != True:
            msg['read'] = True
            mailBox.save(content)
            mailQueue = []

        return json.dumps(msg, indent=4)

    except:
        return json.dumps(False)

@MailBoxPage.route('/')
def index():
    content = mailBox.read()
    msgs = []

    if content is None:
        msgs = []
    elif content.has_key('messages'):
        msgs = copy.deepcopy(content['messages'])
        msgs.sort( lambda A, B: [-1,1][ A['time'] < B['time'] ] )

    host = "%s:%s" % server.hostInfo
    mailCount = len(msgs)
    
    for each in msgs:
        emsg = email.message_from_string(each['data'])
        title = ''
        if emsg['subject'] is not None:
            title += emsg['subject']
        else:
            title += emsg.get_payload()

        each['title'] = title[:40]
        print each['title']

    return render("index.html",{ 'messages':msgs, 'host':host })

################################################################################
# Start
def start():
    try:
        print 'Mail server starts at localhost:' + str(pt)
        server.setup()

        print 'MailBox WebPage starts at localhost:8080'
        bottle.debug(True)
        bottle.run(MailBoxPage, host='localhost', port=8080, reloader=False)
    except Exception, e:
        print "Fault Happens"
    finally:
        server.close()


pt = 4567
server = MailServerHandler(('127.0.0.1', pt))

start()
