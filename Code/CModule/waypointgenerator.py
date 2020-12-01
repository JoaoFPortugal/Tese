import random as random
import sys


def input(numberofwaypoints):

    maxlatitude = 43
    minlatitude = 36

    minlongitude = -9.14
    maxlongitude = 3.25

    latitude, longitude = 0, 0
    altitude = 0
    i = 0
    print(numberofwaypoints)
    while i != numberofwaypoints:
        latitude = round(random.uniform(minlatitude, maxlatitude), 4)
        longitude = round(random.uniform(minlongitude, maxlongitude), 4)
        altitude = random.randint(30000, 30000)
        print(str(latitude) + " " + str(longitude) + " " + str(altitude))
        i = i + 1

    return 0


if __name__ == "__main__":
    numb = sys.argv[1]
    input(int(numb))
