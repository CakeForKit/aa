import pandas as pd
import numpy as np
from geopy.distance import geodesic
from geopy.geocoders import Nominatim

N = 10
V = 1

dirIn = 'in_data'
dirOut = 'in_data'
with open(f'{dirIn}/cities{N}_{V}.txt', encoding="utf-8") as f:
    cities = list(map(lambda x: x.rstrip(), f.readlines()))
print('len =', len(cities))
print(cities)

# Создаем геокодер
geolocator = Nominatim(user_agent="my_agent", timeout=3)

# Получаем координаты городов
coordinates = {}
for city in cities:
    location = geolocator.geocode(city + ", Россия")
    coordinates[city] = (location.latitude, location.longitude)

# Создаем матрицу расстояний
distances = np.zeros((len(cities), len(cities)))

for i, city1 in enumerate(cities):
    for j, city2 in enumerate(cities):
        distance = int(geodesic(coordinates[city1], coordinates[city2]).kilometers)
        distances[i][j] = distance

# Создаем DataFrame
df = pd.DataFrame(distances, index=cities, columns=cities)

# Сохраняем в CSV
df.to_csv(f'{dirOut}/cities{N}_{V}.csv')






