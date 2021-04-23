from django.db import models
from django.core.files import File
import os
import urllib

class Plant(models.Model):
	# Fields
	name = models.CharField(max_length=255)
	image_file = models.ImageField(upload_to='capture')
	image_url = models.URLField()

def get_remote_image(self):
	if self.image_url and not self.image_file:
		result = urllib.request.urlretrieve(self.image_url)
		self.image_file.save(
			os.path.basename(self.image_url),
			File(open(result[0]))
		)
	self.save()