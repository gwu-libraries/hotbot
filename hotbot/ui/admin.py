from django.contrib import admin
from ui.models import Sensor, Reading
from tastypie.admin import ApiKeyInline
from django.contrib.auth.admin import UserAdmin
from django.contrib.auth.models import User

# Register your models here.

class UserModelAdmin(UserAdmin):
    inlines = UserAdmin.inlines + [ApiKeyInline]

class SensorAdmin(admin.ModelAdmin):
    fields = ['macaddr', 'name']
    list_display = ('macaddr', 'name')
    search_fields = ['macaddr', 'name']

class ReadingAdmin(admin.ModelAdmin):
    fields = ['sensor', 'metric', 'value', 'timestamp']
    list_display = ('sensor', 'metric', 'value', 'timestamp')
    search_fields = ['sensor']
    date_hierarchy = 'timestamp'

admin.site.unregister(User)
admin.site.register(User, UserModelAdmin)
admin.site.register(Sensor, SensorAdmin)
admin.site.register(Reading, ReadingAdmin)
