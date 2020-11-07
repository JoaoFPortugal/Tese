from random import *

def input(numberofrestrictions):
    n=5

    maxlongitude = 180
    minlongitude = -180

    maxlatitude = 90
    minlatitude = -90
    latitude,longitude = 0,0
    altitude = 0

    latitude = round(random.uniform(minlatitude,maxlongitude),2)
    longitude = round(random.uniform(minlongitude,maxlongitude),2)
    altitude = random.randint(5000,30000)
    print(latitude + " " + longitude + " " + altitude)
    print(0)

    latitude = round(random.uniform(minlatitude,maxlongitude),2)
    longitude = round(random.uniform(minlongitude,maxlongitude),2)
    altitude = random.randint(5000,30000)

    print(latitude + " " + longitude + " " + altitude)
    i = 1

    print(numberofrestrictions)

    while(i!=numberofrestrictions):

        latitude = round(random.uniform(minlatitude,maxlongitude),2)
        longitude = round(random.uniform(minlongitude,maxlongitude),2)
        altitude = random.randint(5000,30000)
        radius = round(random.uniform(1,15),1)
        print(0 + " " + latitude + " " + longitude + " " + altitude + " " + radius)
        i++

    return 0