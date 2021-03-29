from django.db import models

class User(models.Model):
	# Fields
	name = models.CharField(max_length=50)
	email = models.CharField(max_length=50)
	age = models.IntegerField()
	notify = models.BooleanField()
	admin = models.BooleanField() # 1 if admin, 0 otherwise

	# Methods
	def toggle_notification(self):
		self.notify = not self.notify
	def toggle_admin(self):
		self.admin = not self.admin

class Greenhouse(models.Model):
	# Fields
	name = models.CharField(max_length=100)
	postal_code = models.IntegerField()
	city = models.CharField(max_length=100)
	state = models.CharField(max_length=50)
	country = models.CharField(max_length=100)
	temperature_enabled = models.BooleanField()
	humidity_enabled = models.BooleanField()
	light_enabled = models.BooleanField()
	temperature_setpoint = models.IntegerField()
	humidity_setpoint = models.IntegerField()
	light_setpoint = models.IntegerField()

	# Methods
	def toggle_temperature(self):
		# send HTTP request |TEMPERATURE|?|
		self.temperature_enabled = not self.temperature_enabled
	def toggle_humidity(self):
		self.humidity_enabled = not self.humidity_enabled
	def toggle_light(self):
		self.light_enabled = not self.light_enabled
	def set_temperature(self, setpoint):
		self.temperature_enabled = True
		self.temperature_setpoint = setpoint
	def set_humidity(self, setpoint):
		self.humidity_enabled = True
		self.humidity_setpoint = setpoint
	def set_brightness(self, setpoint):
		self.light_enabled = True
		self.light_setpoint = setpoint
	def edit_address(self, new_address):
		self.name = new_address.name
		self.postal_code = new_address.postal_code
		self.city = new_address.city
		self.state = new_address.state
		self.country = new_address.country

class Plant(models.Model):
	# Fields
	name = models.CharField(max_length=100)
	species = models.CharField(max_length=100)
	birthday = models.DateField(auto_now=False, auto_now_add=False)
	ripeness = models.CharField(max_length=50) # we should change this field type
	last_watered = models.DateField(auto_now=True, auto_now_add=False)
	watering_interval = models.IntegerField()