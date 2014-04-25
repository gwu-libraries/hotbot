from tastypie.authentication import ApiKeyAuthentication, \
    MultiAuthentication, Authentication
from tastypie.authorization import DjangoAuthorization
from tastypie.resources import ModelResource
from ui.models import Sensor, Reading


class ReadingResource(ModelResource):
    class Meta:
	authentication = MultiAuthentication(ApiKeyAuthentication(),
                                             Authentication())
        authorization = DjangoAuthorization()
