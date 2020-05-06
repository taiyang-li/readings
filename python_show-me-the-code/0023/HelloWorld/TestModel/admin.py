# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.contrib import admin
from .models import Test, Tag, Contact


"""
class ContactAdmin(admin.ModelAdmin):
    fields = ('name', 'email')
"""

class TagInline(admin.TabularInline):
    model = Tag

class ContactAdmin(admin.ModelAdmin):
    inlines = [TagInline]  # Inline
    fieldsets = (
            ['Main',{
                'fields':('name','email'),
                }],
            ['Advance',{
                'classes': ('collapse',), # CSS
                'fields': ('age',),
                }]
            )
    list_display = ('name','age', 'email') 
    search_fields = ('name',)

    # Register your models here.
admin.site.register([Test, Tag])
admin.site.register(Contact, ContactAdmin)


