import random as random
import sys


def input(numberofrestrictions):

    maxlatitude = 43
    minlatitude = 36

    minlongitude = -9.14
    maxlongitude = 3.25


    latitude, longitude = 0, 0
    altitude = 0

    latitude = round(random.uniform(minlatitude, maxlatitude), 4)
    longitude = round(random.uniform(minlongitude, maxlongitude), 4)
    altitude = random.randint(30000,30000)
    print(str(latitude) + " " + str(longitude) + " " + str(altitude))
    print(0)

    latitude = round(random.uniform(minlatitude, maxlatitude), 4)
    longitude = round(random.uniform(minlongitude, maxlongitude), 4)
    altitude = random.randint(30000,30000)

    print(str(latitude) + " " + str(longitude) + " " + str(altitude))
    i = 0

    print(numberofrestrictions)

    while i != numberofrestrictions:

        latitude = round(random.uniform(minlatitude, maxlatitude), 4)
        longitude = round(random.uniform(minlongitude, maxlongitude), 4)
        altitude = random.randint(30000, 30000)
        radius = round(random.uniform(5,15),2)
        print("0" + " " + str(latitude) + " " + str(longitude) + " " + str(altitude) + " " + str(radius))
        i = i+1

    print(30000)
    print(350)
    print(2)
    print(95000)
    return 0


if __name__ == "__main__":
    numb = sys.argv[1]
    input(int(numb))
