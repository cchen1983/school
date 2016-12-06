# Django View Handler for Workflow page
# cchen @ 2016.09.09
import sys
import datetime
from django.shortcuts import render
from django.http import HttpResponse, JsonResponse, Http404
from django.template import RequestContext, loader
from django.contrib.auth.decorators import login_required

from django.core.exceptions import ObjectDoesNotExist

#from mysqlUtils import dbQuery

from query.models import *

import datetime
from decimal import Decimal

@login_required
def index(request):
    return render(request, 'workflow/index.html')

# Membership Verification
@login_required
def check_membership(request):
    membershipNo = request.POST.get('membershipNo')
    resp = ''
    try:
        res = Membership.objects.get(id=membershipNo)
        resp = res.balance
    except:
        resp = 'NotExist'

    return HttpResponse(resp)

# Working Form Render
@login_required
def reg_form_view(request):
    tp = request.GET.get('type')
    if tp == 'mem_new':
        return render(request, 'workflow/member_new.html')
    elif tp == 'mem_rec':
        return render(request, 'workflow/member_recharge.html')
    elif tp == 'exp_prod':
        products = Product.objects.all()
        return render(request, 'workflow/exp_product.html', {'products': products})
    elif tp == 'exp_other':
        return render(request, 'workflow/exp_other.html')
    elif tp == 'prc_new':
        products = Product.objects.all()
        return render(request, 'workflow/prc_new.html', {'products': products})
    elif tp == 'act_promo':
        products = Product.objects.all()
        return render(request, 'workflow/act_promo.html', {'products': products})
    elif tp == 'act_discount':
        return render(request, 'workflow/act_discount.html')

# Membership register handler
@login_required
def add_new_member(request):
    name = request.POST.get('name')
    phone = request.POST.get('phone')
    gender = request.POST.get('gender')
    birthday = request.POST.get('birthday')
    balance = request.POST.get('balance')
    passphrase = request.POST.get('passphrase')
    address = request.POST.get('address')
    
    resp = 'OK'

    try:
        cus = Customer(name=name, phone=phone, address=address, gender=gender, birthday=birthday)
        print cus, cus.name, cus.phone, cus.address, cus.gender, cus.birthday
        cus.save()
        print 'cus save ok.'
        mem = Membership(balance=balance, passphrase=passphrase, customerNo=cus)
        print mem
        mem.save() 
        print 'mem save ok'
    except:
        print >> sys.stderr, traceback.format_exc()
        resp = 'create member error'

    return HttpResponse(resp)

# Membership balance recharging
@login_required
def member_recharge(request):
    membershipNo = request.POST.get('membershipNo')
    balance = request.POST.get('balance')
    
    resp = 'OK'

    try:
        mem = Membership.objects.get(id=membershipNo)
        mem.balance = mem.balance + Decimal(balance)
        mem.save()
    except:
        print >> sys.stderr, traceback.format_exc()
        resp = 'recharge error'    

    return HttpResponse(resp)

# Products new/update handler 
@login_required
def exp_product_reg(request):
    resp = 'OK'
    needUpdate = True

    productNo = request.POST.get('product')
    count = request.POST.get('count')
    details = request.POST.get('details')
    print productNo, count, details
    try:
        if productNo == "new":
            new_name = request.POST.get('product_new')
            new_price= request.POST.get('product_price')
            prod = Product(name=new_name, price=new_price, count=count)
            prod.save()
            productNo = prod.id
            needUpdate = False

        payment = request.POST.get('payment')
        prod = Product.objects.get(id=productNo)
        exp = Expenditure(payment=payment, details=details, productNo=prod, count=count)
        exp.save()

        if needUpdate:
            prod.count = prod.count + long(count)
            prod.save()
        
    except:
        print >> sys.stderr, traceback.format_exc()
        resp = 'exp product reg error'

    return HttpResponse(resp)

# Ohter expenditures handler
@login_required
def exp_other_reg(request):
    resp = 'OK'

    payment = request.POST.get('payment')
    details = request.POST.get('details')
    
    try:
        exp = Expenditure(payment=payment, details=details)
        exp.save()
    except:
        print >> sys.stderr, traceback.format_exc()
        resp = 'exp other reg error'

    return HttpResponse(resp)

# Customer Purchasing Handler
@login_required
def purc_reg(request):
    resp = 'OK'
    productNo = request.POST.get('product')
    price = Decimal(request.POST.get('price'))
    count = request.POST.get('count')
    membershipNo = request.POST.get('membershipNo')
    payment = Decimal(request.POST.get('payment'))
    balance = Decimal(0)
    mem = None

    if membershipNo:
        mem = Membership.objects.get(id=membershipNo)
        balance = mem.balance

    charge = price * int(count)
    bcharge = charge - payment

    if mem:
        mem.balance = balance - bcharge
        mem.save()

    prod = Product.objects.get(id=productNo)
    prod.count = prod.count - int(count) 
    prod.save()

    pur = Purchasing(productNo=prod, membershipNo=mem, count=count, payment=charge)
    pur.save()

    return HttpResponse(resp)

# Yihang Zhao @ 20161018
# New Promotion Handler
@login_required
def act_promo_reg(request):
    resp = 'OK'
    productNo = request.POST.get('product')
    n1 = request.POST.get('n1')
    details = request.POST.get('details')
    valid_from = request.POST.get('valid_from')
    valid_to = request.POST.get('valid_to')
    target = request.POST.get('target')

    prod = Product.objects.get(id=productNo)
    promo = Promotion(productNo=prod, n1=n1, valid_from=valid_from, valid_to=valid_to, details=details, target=target)
    promo.save()
    return HttpResponse(resp)

# Saheed @ 20161019
# New Discount Handler
@login_required
def act_discount_reg(request):
    resp = 'OK'
    discount = request.POST.get('discount')
    details = request.POST.get('details')
    valid_from = request.POST.get('valid_from')
    valid_to = request.POST.get('valid_to')
    target = request.POST.get('target')

    try:
        print discount, valid_from, valid_to, target, details
        dis = Discount(disc=discount, valid_from=valid_from, valid_to=valid_to, details=details, target=target)
        dis.save()
    except:
        resp = sys.exc_info()[0]
        print "Unexpected error:", sys.exc_info()
        
    return HttpResponse(resp)

# cchen @ 20161020
# Query discount and promotion info
@login_required
def act_info_get(request):
    productNo = request.POST.get('product')

    n1 = 0
    disc = 1.0
    promo_tgt = 'All'
    disc_tgt = 'All'

    try:
        today = datetime.datetime.now().date()

        # get active discount info
        dclist = Discount.objects.all()
        active_discount = None
        if len(dclist) > 0:
            active_discount = dclist[0]
        if active_discount and active_discount.valid_from.date() <= today and active_discount.valid_to.date() >= today:
            disc_tgt = active_discount.target
            disc = active_discount.disc

        # get promotion info for selected product
        promo = Promotion.objects.get(productNo=productNo)
        print promo
        if promo.valid_from.date() <= today and promo.valid_to.date() >= today:
            promo_tgt = promo.target
            n1 = promo.n1

    except:
        print "act_info_get:", sys.exc_info()[0] 
 

    return JsonResponse({"n1": n1, "disc": disc, "promo_tgt":promo_tgt, "disc_tgt":disc_tgt}) 
