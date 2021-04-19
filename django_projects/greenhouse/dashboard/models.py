from django.db import models

class Plant(models.Model):
	# Fields
	name = models.CharField(max_length=255)
	plant_photo = models.ImageField(upload_to='capture')