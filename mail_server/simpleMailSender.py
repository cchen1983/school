import sys
import smtplib
from email.mime.text import MIMEText

# text/plain message
contentFile = sys.argv[2]

fp = open(contentFile, 'rb')
msg = MIMEText(fp.read())
fp.close()

# default account
fr = "test@test.com"
to = sys.argv[1]

# parse the target server addr
# srvname = to[(to.find('@') + 1) : ]
srvname = "localhost"
print "target server domain: " + srvname

# server port
srvport = 4567    #default

sub = 'The contents of %s' % contentFile 

if sys.argv[3]:
    sub = sys.argv[3]

msg['Subject'] = sub
msg['From'] = fr
msg['To'] = to

# envelope header.
s = smtplib.SMTP(srvname, srvport)
s.sendmail(fr, to, msg.as_string())
s.quit()
