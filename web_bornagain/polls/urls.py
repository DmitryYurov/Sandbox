from django.conf.urls import url

from . import views

urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^view2/', views.yet_another_view, name='another_view'),
]
