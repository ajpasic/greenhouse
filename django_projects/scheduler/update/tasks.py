# Create your tasks here

from celery import shared_task

@shared_task
def detect_and_send():
    # run Max's code
    import sprouttestintegration
