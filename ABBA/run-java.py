import os, sys, re, subprocess, glob

if len(sys.argv) < 2:
    print("Использование: python run-java.py <путь_к_java_файлу>")
    sys.exit(1)

target_file = os.path.abspath(sys.argv[1])

# Находим корень проекта (ищем папку src)
current = os.path.dirname(target_file)
while current != os.path.dirname(current):  # пока не дошли до корня диска
    if os.path.exists(os.path.join(current, 'src', 'main', 'java')):
        workspace = current
        break
    current = os.path.dirname(current)
else:
    print("Ошибка: не найден корень проекта с src/main/java")
    sys.exit(1)

print(f"Корень проекта: {workspace}")
os.chdir(workspace)

# Компилируем все файлы
out_dir = 'out'
os.makedirs(out_dir, exist_ok=True)
java_files = glob.glob('src/main/java/**/*.java', recursive=True)

if not java_files:
    print("Ошибка: не найдены .java файлы")
    sys.exit(1)

print(f"Компилируем {len(java_files)} файлов...")
result = subprocess.run(['javac', '-d', out_dir, '-sourcepath', 'src/main/java', '-encoding', 'UTF-8'] + java_files)
if result.returncode != 0:
    print("Ошибка компиляции!")
    sys.exit(1)

# Определяем пакет и класс
try:
    with open(target_file, 'r', encoding='utf-8') as f:
        content = f.read()
        package_match = re.search(r'^\s*package\s+([\w.]+)\s*;', content, re.MULTILINE)
        package = package_match.group(1) if package_match else ''
except Exception as e:
    print(f"Ошибка чтения файла: {e}")
    sys.exit(1)

class_name = os.path.splitext(os.path.basename(target_file))[0]
full_class = f"{package}.{class_name}" if package else class_name

# Запускаем
print(f"\nЗапускаем {full_class}...\n" + "="*50)
subprocess.run(['java', '-cp', out_dir, full_class])