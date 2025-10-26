import os
import sys
import subprocess
import glob

def main():
    if len(sys.argv) < 2:
        print("Использование: python run-java.py <путь_к_java_файлу>")
        sys.exit(1)

    java_file = sys.argv[1]
    
    # Проверяем, что файл существует и это .java файл
    if not os.path.isfile(java_file) or not java_file.endswith('.java'):
        print(f"Ошибка: файл не существует или не .java файл: {java_file}")
        sys.exit(1)
    
    print(f"Обрабатываем файл: {java_file}")
    
    # Определяем корневую директорию проекта
    project_root = find_project_root(java_file)
    if not project_root:
        print("Не удалось найти корень проекта")
        sys.exit(1)
        
    print(f"Корень проекта: {project_root}")
    os.chdir(project_root)
    
    # Компилируем и запускаем
    if compile_and_run(java_file, project_root):
        print("\nПрограмма завершена успешно")
    else:
        print("Ошибка выполнения")
        sys.exit(1)

def find_project_root(java_file_path):
    """Находит корень проекта по структуре Maven/Gradle"""
    current_dir = os.path.dirname(java_file_path)
    
    # Ищем вверх по директориям признаки проекта Java
    while current_dir != os.path.dirname(current_dir):
        # Проверяем наличие стандартных структур
        if (os.path.exists(os.path.join(current_dir, 'src', 'main', 'java')) or
            os.path.exists(os.path.join(current_dir, 'pom.xml')) or
            os.path.exists(os.path.join(current_dir, 'build.gradle'))):
            return current_dir
        
        # Если находимся в pract2, используем его родительскую директорию
        if os.path.basename(current_dir) == 'pract2':
            return os.path.dirname(current_dir)
            
        current_dir = os.path.dirname(current_dir)
    
    # Если ничего не нашли, возвращаем директорию где находится Java файл
    return os.path.dirname(java_file_path)

def compile_and_run(java_file, project_root):
    """Компилирует и запускает Java файл"""
    
    # Определяем путь к исходникам
    src_path = None
    possible_src_paths = [
        os.path.join(project_root, 'pract2', 'src', 'main', 'java'),
        os.path.join(project_root, 'src', 'main', 'java'),
        os.path.join(project_root, 'src'),
        os.path.dirname(java_file)
    ]
    
    for path in possible_src_paths:
        if os.path.exists(path):
            src_path = path
            break
    
    if not src_path:
        print("Не найдена директория с исходниками")
        return False
    
    print(f"Директория исходников: {src_path}")
    
    # Создаем директорию для скомпилированных классов
    out_dir = os.path.join(project_root, 'out')
    os.makedirs(out_dir, exist_ok=True)
    
    # Находим все Java файлы в директории исходников
    java_files = glob.glob(os.path.join(src_path, '**', '*.java'), recursive=True)
    
    if not java_files:
        print("Не найдены .java файлы для компиляции")
        return False
    
    print(f"Найдено {len(java_files)} .java файлов")
    
    # Компилируем
    print("Компилируем...")
    compile_result = subprocess.run([
        'javac', 
        '-d', out_dir,
        '-sourcepath', src_path,
        '-encoding', 'UTF-8'
    ] + java_files)
    
    if compile_result.returncode != 0:
        print("Ошибка компиляции!")
        return False
    
    # Определяем полное имя класса для запуска
    class_name = get_full_class_name(java_file, src_path)
    if not class_name:
        print("Не удалось определить имя класса")
        return False
    
    print(f"Запускаем класс: {class_name}")
    print("=" * 50)
    
    # Запускаем
    run_result = subprocess.run([
        'java',
        '-cp', out_dir,
        class_name
    ])
    
    return run_result.returncode == 0

def get_full_class_name(java_file, src_path):
    """Определяет полное имя класса из Java файла"""
    try:
        with open(java_file, 'r', encoding='utf-8') as f:
            content = f.read()
            
        # Ищем package
        package_line = None
        for line in content.split('\n'):
            line = line.strip()
            if line.startswith('package '):
                package_line = line
                break
        
        # Извлекаем имя пакета
        package = None
        if package_line:
            package = package_line.replace('package', '').replace(';', '').strip()
        
        # Имя класса - это имя файла без расширения
        class_name = os.path.splitext(os.path.basename(java_file))[0]
        
        # Полное имя класса
        if package:
            return f"{package}.{class_name}"
        else:
            return class_name
            
    except Exception as e:
        print(f"Ошибка при чтении файла: {e}")
        return None

if __name__ == "__main__":
    main()