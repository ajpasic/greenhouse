from django.shortcuts import render
from django.http import HttpResponse

# Create your views here.

def test(request):
	# to populate fields from data, define a context and pass it to render()
	return render(request, 'test.html')

def gauge(request):
	return render(request, 'gauge.html')