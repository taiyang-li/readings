#!/usr/bin/env python
# coding: utf-8

import wave, pyaudio
from aip import AipSpeech
import sys
import webbrowser

CHUNK = 1024
FORMAT = pyaudio.paInt16
RATE = 16000
CHANNELS = 1
RECORD_SECONDS = 10
WAV_PATH = './record.wav'

def recordWave():
    pa = pyaudio.PyAudio()
    stream = pa.open(format=FORMAT,
                     channels=CHANNELS,
                     rate=RATE,
                     input=True,
                     frames_per_buffer=CHUNK)
    print 'Recording...'
    buffer = []
    for i in range(0, int(RATE/CHUNK*RECORD_SECONDS)):
        audio_data = stream.read(CHUNK)
        buffer.append(audio_data)
    print 'Record Done'
    stream.stop_stream()
    stream.close()
    pa.terminate()
    wf = wave.open(WAV_PATH, 'wb')
    wf.setnchannels(CHANNELS)
    wf.setsampwidth(pa.get_sample_size(FORMAT))
    wf.setframerate(RATE)
    wf.writeframes(b''.join(buffer))
    wf.close()

def get_file_content(filePath):
    with open(filePath, 'rb') as fp:
        return fp.read()

def browser_open_text(text):
    if text is None:
        return
    
    url = "http://www.baidu.com"
    if text.startswith(u"谷歌") or text.startswith("google"):
        url = "http://www.google.com"
    elif text.startswith(u"必应") or text.startswith("bing"):
        url = "http://cn.bing.com"
    webbrowser.open_new_tab(url)

# record audio to .wav file
recordWave()

# speech recognition
# API_ID, API_KEY, SECRET_KEY都可从百度开放平台上注册语音引用获取
APP_ID = 'xxxx'
API_KEY = 'xxxx'
SECRET_KEY = 'xxxx'
client = AipSpeech(APP_ID, API_KEY, SECRET_KEY)
output = client.asr(get_file_content(WAV_PATH), 'wav', RATE, { 'lan': 'zh', })
if output['err_no'] != 0:
    print "speeach recognition failed, %s" % (output['err_msg'])
    sys.exit(-1)
speech_text = output['result'][0]
print "speeach text is %s" % speech_text

# open browser by text
browser_open_text(speech_text)
