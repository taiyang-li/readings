import picamera
import time

def getCurrentTime():
    (year, month, day, hour, minute, second, _, _, _) = time.localtime()
    ret = "%04d%02d%02d%02d%02d%02d" % (year, month, day, hour, minute, second)
    return ret

camera = picamera.PiCamera()
prefix = "yanshi"
path = "/mnt/sandisk/"

while True:
    suffix = getCurrentTime() 
    filename = path + prefix + "_" + suffix + ".jpg"
    print filename
    camera.capture(filename)
    time.sleep(10)
