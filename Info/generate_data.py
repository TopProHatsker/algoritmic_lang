import random

# Начальные данные
data = [
    ("Khabarovskaya", [10, 9, 7]),
    ("Novosibirskaya", [15, 15, 3]),
    ("Urengoyaskya", [25, 23, 7]),
    ("Krasnodarskaya", [7, 7, 5]),
    ("Kushevskoe", [5, 4, 3]),
    ("Stavropolskaya", [15, 7, 3]),
    ("Gatchinskaya", [10, 0, 5]),
    ("Nord Stream - 2", [1400, 2200, 1]),
    ("Nord Stream", [1400, 2000, 1]),
    ("Yamal - Europe", [1400, 3000, 0]),
    ("Urengoi - Uzhgorod", [1000, 5000, 0]),
    ("Blue Stream", [700, 850, 0]),
    ("Turkish Stream", [700, 1450, 1]),
    ("Power of Siberia", [1400, 1500, 0]),
    ("Power of Siberia - 2", [1400, 4000, 0])
]

# Функция для генерации новых записей
def generate_data(num_records):
    new_data = []
    for _ in range(num_records):
        name = f"Region_{random.randint(1, 100)}"
        values = [random.randint(0, 3000) for _ in range(3)]
        new_data.append((name, values))
    return new_data

# Генерация дополнительных записей
additional_data = generate_data(50) # Генерируем 50 новых записей

# Объединяем данные
all_data = data + additional_data

# Запись в файл
with open("regions_data.txt", "w") as f:
    # Записываем количество записей
    f.write(f"{len(all_data)} {len(all_data[0][1])}\n")
    
    # Записываем данные
    for name, values in all_data:
        f.write(f"{name}\n")
        for value in values:
            f.write(f"{value}\n")
