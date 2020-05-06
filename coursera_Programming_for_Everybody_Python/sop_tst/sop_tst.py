#!/usr/local/bin/python

import urllib
import json

serviceurl = 'http://maps.googleapis.com/maps/api/geocode/json?'

while True:
    address = raw_input('Entre location')
    if len(address) < 1:
        break

    url = serviceurl + urllib.urlencode({'sensor' : 'false', 'address' : address})
    print 'retrieving', url
    uh = urllib.urlopen(url)
    data = uh.read()
    print 'retrieve', len(data), 'characters'

    try: 
        js = json.loads(str(data))
    except:
        js = None

    if 'status' not in js or js['status'] != 'OK':
        print '==== failure to retrieve ===='
        print data
        continue

    print json.dumps(js, indent=4)
    lat = js["results"][0]["geometry"]["location"]["lat"]
    lng = js["results"][0]["geometry"]["location"]["lng"]
    print 'lat', lat, 'lng', lng
    location = js['results'][0]['formatted_address']
    print location
