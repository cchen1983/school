# Simple Mail Server

    A simple mail server based on SMTP Protocol, 

    Features:

    <Server Side>
    1. Receiving and Parsing mail by SMTP Protocol;
    2. Storing mails to a simple mail database for multiple users;
    3. Send outside mail via Conifurable Proxy SMTP Server;
    4. A simple Mailbox Web page to browse and manage mails.

    <Client Side>
    1. A simple command line tools to send mail to the server;
    2. User can specify receiver and text content of mail.

# Usage

    Run SMTP Server and Mailbox Web Server:

        $ python simpleMailServer.py

        Mailbox WebPage : http://localhost:8080/
        SMTP Server: http://localhost:4567/

    Configure Outgoing Proxy:

         Edit outsrv_login.txt with account/password of gmail
         Restart server.

    Send mail using Client:
    
        $ python simpleMailSender.py <to> <filename_content> <subject>

# Pre-requisits Software

    python & django


