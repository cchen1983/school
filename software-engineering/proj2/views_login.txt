# cchen @ 2016.08.30
# User Account Login/Register Handler

from django.shortcuts import render, redirect
from django.http import HttpResponse
from django.template import RequestContext, loader

from django.contrib.auth.models import User
from django.contrib.auth import authenticate, login, logout
from django.core.exceptions import ValidationError
from django.core.validators import validate_email

from django.contrib.auth.decorators import login_required

def login_box(request):
    if request.method == 'POST':
        resp_msg = 'OK'
        if request.POST.get('Login'):
            username = request.POST.get('username')
            password = request.POST.get('password')
        
            user = authenticate(username = username, password = password)
            if user is not None:
                if user.is_active:
                    login(request, user)
                    if not request.POST.get('remember', None):
                        request.session.set_expiry(0)
                else:
                    resp_msg = 'DISABLED'
            else:
                resp_msg = 'Error'

        elif request.POST.get('Register'):
            username = request.POST.get('newusername')
            password = request.POST.get('npassword')
            email = request.POST.get('email')

            # Check if the user name exsists. 
            try:
                User.objects.get(username = username)
                resp_msg = 'USER_EXIST'
                User.objects.get(email = email)
                resp_msg = 'EMAIL_EXIST'
            except User.DoesNotExist:
                print "new user applying..." 

            if resp_msg == 'OK':
                try:
                    validate_email(email)
                    User.objects.create_user(username, email, password)
                    user = authenticate(username = username, password = password)
                    if user is not None:
                        login(request, user)
                    else:
                        resp_msg = 'Error'
                except ValidationError:
                    resp_msg = "EMAIL_INVALID"
        else:
            resp_msg = 'Error'

        return login_ajax_response(request, resp_msg)
    else:
        return render(request, 'login/login.html')

def login_ajax_response(request, msg):
    return render(request, 'login/login_ajax_response.html', {'msg': msg})

@login_required
def logout_page(request):
    logout(request);
    return redirect('/')

@login_required
def account_settings(request):
    if request.method == 'POST':
        password = request.POST.get('npassword')
        resp_msg = 'OK'
        try:
            request.user.set_password(password);
            request.user.save();
        except:
            resp_msg = 'Error'

        return login_ajax_response(request, resp_msg)
    else:
        return render(request, 'login/account_settings.html')
