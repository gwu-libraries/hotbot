from tastypie import fields
from tastypie.authentication import ApiKeyAuthentication, \
    MultiAuthentication, Authentication
from tastypie.authorization import DjangoAuthorization
from tastypie.constants import ALL_WITH_RELATIONS
from tastypie.resources import ModelResource
from ui.models import Sensor, Reading


class SensorResource(ModelResource):
    class Meta:
        queryset = Sensor.objects.all()
	filtering = {
            'macaddr': 'exact',
        }
        authentication = MultiAuthentication(ApiKeyAuthentication(),
                                             Authentication())
        authorization = DjangoAuthorization()


class ReadingResource(ModelResource):
    sensor = fields.ForeignKey(SensorResource, 'sensor')
    class Meta:
	queryset = Reading.objects.all()
        filtering = {
            'sensor': ALL_WITH_RELATIONS
        }
	authentication = MultiAuthentication(ApiKeyAuthentication(),
                                             Authentication())
        authorization = DjangoAuthorization()
