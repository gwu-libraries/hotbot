from django.db import models


class Sensor(models.Model):
    macaddr = models.CharField(max_length=12, db_index=True)
    name = models.CharField(max_length=50, db_index=True)


class Reading(models.Model):
    sensor = models.ForeignKey(Sensor, related_name='sensors')
    metric = models.CharField(max_length=20, db_index=True)
    value = models.FloatField()
    timestamp = models.DateTimeField(db_index=True)
