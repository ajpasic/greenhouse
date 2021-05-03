#from http.server import HTTPServer, BaseHTTPRequestHandler  # necessary libraries
import cv2
import numpy as np
import glob
import random

#Load in the trained YoloV3 model that was trained on google colab
net = cv2.dnn.readNet("yolov3_training_last_sprout.weights", "yolov3_testing_sprout.cfg")
# Objects to be detected
classes = ["Sprout"]
# loading the path to the images
images_path = glob.glob(r"C:\Users\Mjohn\PycharmProjects\PythonWebServer&ObjectDetection\venv\Scripts\images (4).jpg") #Change later

#create a list that holds all of the labels detected from each model

total_labels = []
label = []

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
            cv2.rectangle(img, (x, y), (x + w, y + h), (255*(((confidences[i-1])-0.75))/.25, 0, 0), 1)
            #cv2.putText(img, str(j), (x, y-5), font, 1, (0, 0, 255), 1)
            j = j + 1

    j = 1
    for i in range(len(boxes)):
        if i in indexes:
            #cv2.putText(img, "{:.2f}".format(confidences[j-1] * 100), (460, 20*j), font, 1, (63, 255, 4), 1)
            #cv2.putText(img, str(j), (430, 20 * j), font, 1, (0, 0, 255), 1)
            j = j + 1


    #cv2.putText(img, 'Sprout(s):', (0, 20), font, 1, (63, 255, 4), 1)
    #cv2.putText(img, str(len(boxes)), (80, 20), font, 1, (0, 0, 255), 1)
    scale_percent = 100  # percent of original size
    width = int(img.shape[1] * scale_percent / 100)
    height = int(img.shape[0] * scale_percent / 100)
    dim = (width, height)
    # resize image
    resized = cv2.resize(img, dim, interpolation=cv2.INTER_AREA)


    #cv2.imshow("Image", resized)
    cv2.imwrite("Detected_Image.jpg", resized)
    if (label):
        total_labels.append(label)

    #key = cv2.waitKey(0)

#cv2.destroyAllWindows()

#Load in the trained YoloV3 model that was trained on google colab
net = cv2.dnn.readNet("yolov3_training_last_flower.weights", "yolov3_testing_flower.cfg")
# Objects to be detected
classes = ["flower"]
#create a list that holds all of the labels detected from each model

layer_names = net.getLayerNames()
output_layers = [layer_names[i[0] - 1] for i in net.getUnconnectedOutLayers()]

#cycle through the testing image set
for img_path in images_path:
    # loading the image from the image path
    #img = cv2.imread(img_path)
    # resize so that all images are analyzed and viewed the same
    #img = cv2.resize(img, None, fx=0.4, fy=0.4)
    # storing the image dimensions
    height, width, channels = resized.shape
    # Detecting objects
    blob = cv2.dnn.blobFromImage(resized, 0.00392, (416, 416), (0, 0, 0), True, crop=False)

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
            cv2.rectangle(resized, (x, y), (x + w, y + h), (0,255*(((confidences[i-1])-0.75))/.25, 0), 1)
            #cv2.putText(resized, str(j), (x, y-5), font, 1, (0, 0, 255), 1)
            j = j + 1

    j = 1
    for i in range(len(boxes)):
        if i in indexes:
            #cv2.putText(resized, "{:.2f}".format(confidences[j-1] * 100), (460, 20*j), font, 1, (63, 255, 4), 1)
            #cv2.putText(resized, str(j), (430, 20 * j), font, 1, (0, 0, 255), 1)
            j = j + 1


    #cv2.putText(resized, 'Flower(s):', (0, 40), font, 1, (63, 255, 4), 1)
    #cv2.putText(resized, str(len(boxes)), (80, 40), font, 1, (0, 0, 255), 1)
    #scale_percent = 220  # percent of original size
    #width = int(resized.shape[1] * scale_percent / 100)
    #height = int(resized.shape[0] * scale_percent / 100)
    #dim = (width, height)
    # resize image
    #resized = cv2.resize(resized, dim, interpolation=cv2.INTER_AREA)


    #cv2.imshow("Image", resized)
    #cv2.imwrite("Detected_Image.jpg", resized)

    total_labels.append(label)

    #key = cv2.waitKey(0)

#cv2.destroyAllWindows()

#Load in the trained YoloV3 model that was trained on google colab
net = cv2.dnn.readNet("yolov3_training_final.weights", "yolov3_testing_fruit.cfg")
# Objects to be detected
classes = ["fruit"]

#create a list that holds all of the labels detected from each model

layer_names = net.getLayerNames()
output_layers = [layer_names[i[0] - 1] for i in net.getUnconnectedOutLayers()]

#cycle through the testing image set
for img_path in images_path:
    # loading the image from the image path
    #img = cv2.imread(img_path)
    # resize so that all images are analyzed and viewed the same
    #img = cv2.resize(img, None, fx=0.4, fy=0.4)
    # storing the image dimensions
    height, width, channels = resized.shape
    # Detecting objects
    blob = cv2.dnn.blobFromImage(resized, 0.00392, (416, 416), (0, 0, 0), True, crop=False)

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
            cv2.rectangle(resized, (x, y), (x + w, y + h), (0, 0, 255*(((confidences[i-1])-0.75))/.25), 1)
            #cv2.putText(resized, str(j), (x, y-5), font, 1, (0, 0, 255), 1)
            j = j + 1

    j = 1
    for i in range(len(boxes)):
        if i in indexes:
            #cv2.putText(resized, "{:.2f}".format(confidences[j-1] * 100), (460, 20*j), font, 1, (63, 255, 4), 1)
            #cv2.putText(resized, str(j), (430, 20 * j), font, 1, (0, 0, 255), 1)
            j = j + 1


    #cv2.putText(resized, 'Fruit(s):', (0, 60), font, 1, (63, 255, 4), 1)
    #cv2.putText(resized, str(len(boxes)), (80, 60), font, 1, (0, 0, 255), 1)
    print(label)
    #scale_percent = 220  # percent of original size
    #width = int(resized.shape[1] * scale_percent / 100)
    #height = int(resized.shape[0] * scale_percent / 100)
    #dim = (width, height)
    # resize image
    #resized = cv2.resize(img, dim, interpolation=cv2.INTER_AREA)

    #Comment out  cv2.imshow("Image", resized), key = cv2.waitKey(0), cv2.destroyAllWindows() to not display image

    cv2.imshow("Image", resized)
    cv2.imwrite("Detected_Image.jpg", resized)

    total_labels.append(label)

    key = cv2.waitKey(0)

cv2.destroyAllWindows()

print(total_labels)

count_sprout = 0;
count_flower = 0;
count_fruit = 0;

for i in range(0, len(total_labels)):
    if total_labels[i] == 'Sprout':
        count_sprout = count_sprout + 1;
    elif total_labels[i] == 'fruit':
        count_fruit = count_flower + 1;
    elif total_labels[i] == 'flower':
        count_flower = count_flower + 1;

import smtplib

EMAIL_ADDRESS = 'reapeatsmartgreenhouse@gmail.com'
EMAIL_PASSWORD = '5qn2jcis'

#write something where it lists what is detected (Weekly email updates!)

with smtplib.SMTP('smtp.gmail.com', 587) as smtp:  # context manager closes connection automatically
    smtp.ehlo()  # identifies with the mail server
    # now encrypt traffic
    smtp.starttls()
    smtp.ehlo()  # identifies with the mail server after encryption
    # log into email address
    smtp.login(EMAIL_ADDRESS, EMAIL_PASSWORD)

    subject = 'Plant Progress Update!'
    body = 'Greetings!\n\n' \
           '' \
           'Your plant has the following attributes detected: ' \
           '{sprout}\n'\
           '{flower}\n' \
           '{fruit}\n' \
           'Best,\nReapEat Support'.format(sprout="Sprout(s)" if count_sprout else "", flower="Flower(s)" if count_flower else "",fruit="Fruit(s)" if count_fruit else "")

    msg = f'Subject: {subject}\n\n{body}'
    #load in emails on list from .txt document
    smtp.sendmail(EMAIL_ADDRESS, 'mjohnsmax@gmail.com', msg)  # (sender, receiver, msg)


