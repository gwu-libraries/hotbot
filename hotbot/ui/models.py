from django.db import models
from django.contrib.auth.models import User

from tastypie.models import create_api_key

models.signals.post_save.connect(create_api_key, sender=User)


class Sensor(models.Model):
    macaddr = models.CharField(max_length=12, db_index=True)
    name = models.CharField(max_length=50, db_index=True)


class Reading(models.Model):
    sensor = models.ForeignKey(Sensor, related_name='sensors')
    metric = models.CharField(max_length=20, db_index=True)
    value = models.FloatField()
    timestamp = models.DateTimeField(db_index=True)
