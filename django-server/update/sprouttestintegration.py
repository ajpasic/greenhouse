import cv2
import numpy as np
import glob
import random

#Load in the trained YoloV3 model that was trained on google colab
net = cv2.dnn.readNet("yolov3_training_last_sprout.weights", "yolov3_testing_sprout.cfg")
# Objects to be detected
classes = ["Sprout"]
# loading the path to the images
images_path = glob.glob(r"/home/adi/greenhouse/django-server/update/capture.jpg") # CHANGE THIS IF PATH IS DIFFERENT!!!

#create a list that holds all of the labels detected from each model

total_labels = []

layer_names = net.getLayerNames()
output_layers = [layer_names[i[0] - 1] for i in net.getUnconnectedOutLayers()]

#cycle through the testing image set
for img_path in images_path:
    # loading the image from the image path
    img = cv2.imread(img_path)
    # resize so that all images are analyzed and viewed the same
    img = cv2.resize(img, None, fx=0.4, fy=0.4)
    # storing the image dimensions
    height, width, channels = img.shape
    # Detecting objects
    blob = cv2.dnn.blobFromImage(img, 0.00392, (416, 416), (0, 0, 0), True, crop=False)

    net.setInput(blob)
    outs = net.forward(output_layers)

    # Displaying the information from the prediction
    class_ids = []
    confidences = []
    boxes = []
    for out in outs:
        for detection in out:
            scores = detection[5:]
            class_id = np.argmax(scores)
            confidence = scores[class_id]
            if confidence > 0.80:
                # Object detected with at least 80 percent confidence

                center_x = int(detection[0] * width)
                center_y = int(detection[1] * height)
                w = int(detection[2] * width)
                h = int(detection[3] * height)

                # Rectangle coordinates
                x = int(center_x - w / 2)
                y = int(center_y - h / 2)

                boxes.append([x, y, w, h])
                confidences.append(float(confidence))
                class_ids.append(class_id)

    indexes = cv2.dnn.NMSBoxes(boxes, confidences, 0.5, 0.4)

    font = cv2.FONT_HERSHEY_PLAIN
    j = 1
    for i in range(len(boxes)):
        if i in indexes:
            x, y, w, h = boxes[i]
            label = str(classes[class_ids[i]])
            cv2.rectangle(img, (x, y), (x + w, y + h), (63, 255, 4), 1)
            cv2.putText(img, str(j), (x, y-5), font, 1, (0, 0, 255), 1)
            j = j + 1

    j = 1
    for i in range(len(boxes)):
        if i in indexes:
            cv2.putText(img, "{:.2f}".format(confidences[j-1] * 100), (460, 20*j), font, 1, (63, 255, 4), 1)
            cv2.putText(img, str(j), (430, 20 * j), font, 1, (0, 0, 255), 1)
            j = j + 1


    cv2.putText(img, 'Sprout(s)', (0, 20), font, 1, (63, 255, 4), 1)

    scale_percent = 220  # percent of original size
    width = int(img.shape[1] * scale_percent / 100)
    height = int(img.shape[0] * scale_percent / 100)
    dim = (width, height)
    # resize image
    resized = cv2.resize(img, dim, interpolation=cv2.INTER_AREA)


    #cv2.imshow("Image", resized)
    #cv2.imwrite("Detected_Image.jpg", resized)

    total_labels.append(label)

#   key = cv2.waitKey(0)
print(total_labels)
#cv2.destroyAllWindows()

import smtplib

EMAIL_ADDRESS = 'reapeatsmartgreenhouse@gmail.com'
EMAIL_PASSWORD = '5qn2jcis'

if (label == "Sprout"):

    with smtplib.SMTP('smtp.gmail.com', 587) as smtp: #context manager closes connection automatically
        smtp.ehlo() #identifies with the mail server
        #now encrypt traffic
        smtp.starttls()
        smtp.ehlo()  # identifies with the mail server after encryption
        #log into email address
        smtp.login(EMAIL_ADDRESS, EMAIL_PASSWORD)


        subject = 'Plant Progress Update!'
        body = 'Greetings!\n\nYour plant has begun sprouting! Congratulations!\n\n\nBest,\nReapEat Support'

        msg = f'Subject: {subject}\n\n{body}'

        smtp.sendmail(EMAIL_ADDRESS, 'mjohnsmax@gmail.com', msg) # (sender, receiver, msg)