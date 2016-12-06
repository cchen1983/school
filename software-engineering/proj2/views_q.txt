# Django View Handler for Query Page
# cchen @ 2016.9.6

from django.shortcuts import render
from django.http import HttpResponse, JsonResponse, Http404
from django.template import RequestContext, loader
from django.contrib.auth.decorators import login_required

#from mysqlUtils import dbQuery

from query.models import *

import datetime

def isModelInstance(x):
    for c in TBL_NAME_LIST:
        if isinstance(x, eval(c)):
            return True
    return False

# Search by condition
@login_required
def cond_query(request):
    fdName = request.POST.get('fdName')
    fdValue = request.POST.get('fdValue')
    tblName = request.POST.get('tblName')
    objs = []
    if fdValue[:1] == '>':
        objs = eval(tblName).objects.filter(**{fdName + '__gt':fdValue[1:]})
    elif fdValue[:1] == '<':
        objs = eval(tblName).objects.filter(**{fdName + '__lt':fdValue[1:]})
    else:
        regex = '(' + str(fdValue) + ')+'
        objs = eval(tblName).objects.filter(**{fdName + '__regex':regex})

    fields = eval(tblName)._meta.fields
    fieldNames = []
    for fd in fields:
        fieldNames.append(fd.name)
    
    tuples = []
    for obj in objs:
        tp = []
        for name in fieldNames:
            o = getattr(obj, name)
            if isModelInstance(o):
                # Just show id for foreginkey object
                o = o.id
            elif isinstance(o, datetime.date) or isinstance(o, datetime.datetime):
                o = str(o)
            tp.append(o)
        tuples.append(tp)

    return render(request, 'query/tableview.html', {'fdNames':fieldNames, 'tuples':tuples})

@login_required
def index(request):
    return render(request, 'query/index.html', {'tbls':TBL_NAME_LIST})

# Retrieving meta-data of requested model
@login_required
def get_meta_fields(request):
    tblName = request.POST.get('tblName')
    fields = eval(tblName)._meta.fields
    fieldNames = []
    for fd in fields:
        fieldNames.append(fd.name)
    return JsonResponse(fieldNames, safe=False)

# Update user input to database
@login_required
def tuple_update(request):
    tblName = request.POST.get('tblName')
    fields = eval(tblName)._meta.fields
    tp = request.POST.getlist('tuple[]')
    tpId = tp[0]
    resp = 'OK' 

    try:
        obj = eval(tblName).objects.get(id=tpId)
        idx = 0
        for fd in fields:
            print idx, fd.name
            print getattr(obj, fd.name)
            print isModelInstance(getattr(obj, fd.name))
            if idx > 0 and not isModelInstance(getattr(obj, fd.name)):
                # Filter the foreginkey object out of iteration
                print fd.name, tp[idx]
                setattr(obj, fd.name, tp[idx])
            idx = idx + 1
        obj.save()
    except Exception:
        print >> sys.stderr, traceback.format_exc()
        resp = 'submit error.'

    return HttpResponse(resp)
