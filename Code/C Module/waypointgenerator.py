import random as random
import sys


def input(numberofwaypoints):

    maxlongitude = 180
    minlongitude = -180

    maxlatitude = 90
    minlatitude = -90
    latitude, longitude = 0, 0
    altitude = 0
    i = 0
    print(numberofwaypoints)
    while i != numberofwaypoints:

        latitude = round(random.uniform(minlatitude,maxlongitude),2)
        longitude = round(random.uniform(minlongitude,maxlongitude),2)
        altitude = random.randint(5000,30000)
        print(str(latitude) + " " + str(longitude) + " " + str(altitude))
        i = i+1

    return 0


if __name__ == "__main__":
    numb = sys.argv[1]
    input(int(numb))
