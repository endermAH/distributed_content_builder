from PIL import Image, ImageDraw
import os
import sys
import time
import random
import pathlib
import json
import math

# PROJECT DEFAULTS
PROJECT_ROOT = "test_files"
PROJECT_ITERATIONS_COUNT = 10
PROJECT_FILE_CHANGE_RATE = 50  # From 0 to 100
PROJECT_FILE_CREATION_RATE = 20
PROJECT_EXECUTOR_PATH = "/Users/evgenijkuratov/CLionProjects/distributed_content_builder/tools/compress_file.py"

# File change defaults
MIN_PIXELS_TO_CHANGE = 10000
MAX_PIXELS_TO_CHANGE = 40000


def get_random_color():
    """ get random color in format (R,G,B) """
    R = random.randint(0, 255)
    G = random.randint(0, 255)
    B = random.randint(0, 255)
    color = (R, G, B)
    return color


def change_file(file_path):
    """ Imitate random file change """
    image = Image.open(file_path)

    pixels_to_change = random.randint(MIN_PIXELS_TO_CHANGE, MAX_PIXELS_TO_CHANGE)
    square_width = round(math.sqrt(pixels_to_change))
    square_x = random.randint(0, image.size[0] - 1 - square_width)
    square_y = random.randint(0, image.size[0] - 1 - square_width)

    shape = [(square_x, square_y), (square_x + square_width, square_y + square_width)]
    img1 = ImageDraw.Draw(image)
    img1.rectangle(shape, fill=get_random_color(), outline="red")

    # ===== DEPRECATED =====
    # pixel_map = image.load()
    # for i in range(pixels_to_change):
    #     random_x = random.randint(0, image.size[0] - 1)
    #     random_y = random.randint(0, image.size[1] - 1)
    #     random_color = get_random_color()
    #     pixel_map[random_x, random_y] = random_color
    # ===== DEPRECATED =====

    image.save(file_path)


def get_project_files(project_root):
    """" Returns list of project files which can be built """
    project_files = []
    for (dirpath, dirnames, filenames) in os.walk(project_root):
        for file in filenames:
            file_path = pathlib.Path(dirpath).joinpath(file)
            if file_path.suffix == ".json":
                with open(file_path.absolute()) as json_file:
                    file_to_add_str = json.loads(json_file.read())["file"]
                file_to_add = pathlib.Path(dirpath).joinpath(file_to_add_str)
                file_to_add_str = file_to_add.absolute()
                project_files.append(file_to_add_str)
    return project_files


def get_desicion(rate):
    """ Return random true or false based on rate from 1 to 100"""
    number = random.randint(1, 100)
    return number <= rate


def create_file(project_root):
    """ Creates new random image in project root and generates json file for this"""
    image = Image.new('RGB', (2048, 2048), "black")

    for i in range(5):
        pixels_to_change = random.randint(MIN_PIXELS_TO_CHANGE, MAX_PIXELS_TO_CHANGE)
        square_width = round(math.sqrt(pixels_to_change))
        square_x = random.randint(0, image.size[0] - 1 - square_width)
        square_y = random.randint(0, image.size[0] - 1 - square_width)
        shape = [(square_x, square_y), (square_x + square_width, square_y + square_width)]
        img1 = ImageDraw.Draw(image)
        img1.rectangle(shape, fill=get_random_color(), outline="red")

    # ===== DEPRECATED =====
    # pixels = image.load()
    # for i in range(image.size[0]):
    #     for j in range(image.size[1]):
    #         pixels[i, j] = get_random_color()
    # ===== DEPRECATED =====

    file_name = "new-image-%s" % time.time()
    png_path = project_root.joinpath(file_name + '.png')
    json_path = project_root.joinpath(file_name + '.json')
    image.save(png_path, 'png')

    file_meta = {
        "file": str(png_path),
        "executor": PROJECT_EXECUTOR_PATH,
        "parameters": ""
    }

    with open(json_path, 'w') as json_file:
        json_file.write(json.dumps(file_meta))

    return png_path


def print_array(array, title):
    """ Prints array and title """
    print(title)
    for item in array:
        print(" - %s" % item)


if __name__ == "__main__":
    total_files_created = []
    total_files_changed = []
    for i in range(PROJECT_ITERATIONS_COUNT):
        print("### ITERATION №%s" % i)
        abs_root_path = pathlib.Path(PROJECT_ROOT).absolute()
        files_to_change = get_project_files(abs_root_path)

        changed_files = []
        created_files = []

        if get_desicion(PROJECT_FILE_CREATION_RATE):
            file = create_file(abs_root_path)
            created_files.append(file)

        for file in files_to_change:
            if get_desicion(PROJECT_FILE_CHANGE_RATE):
                change_file(file)
                changed_files.append(file)

        print_array(changed_files, "Files changed:")
        total_files_changed.extend(changed_files)
        print_array(created_files, "Files created:")
        total_files_created.extend(created_files)
        print("\n")

    print_array(total_files_created, "Total files created:")

