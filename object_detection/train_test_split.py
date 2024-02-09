import os
import glob
import cv2
import random
import shutil

if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(
        description="Split the images into a training set and a testing set."
    )
    parser.add_argument(
        "--project-dir",
        help="Directory name of the project.",
        default="./project_name",
        type=str,
    )
    args = parser.parse_args()

    project_dir = args.project_dir
    all_images = glob.glob(os.path.join(project_dir, 'data/*.jpg'))
    percent_of_data_in_training = 75

    number_of_images_in_train_set = int(len(all_images)*percent_of_data_in_training/100)
    train_set = random.sample(all_images, number_of_images_in_train_set)
    test_set = [image for image in all_images if image not in train_set]
    
    os.makedirs(os.path.join(project_dir,'data/train'), exist_ok=True)
    os.makedirs(os.path.join(project_dir,'data/test'), exist_ok=True)
    for image in all_images:
        if image in train_set:
            shutil.move(image, os.path.join(project_dir, 'data', 'train', image.replace('golf_ball/data/','')))
        else:
            shutil.move(image, os.path.join(project_dir, 'data', 'test', image.replace('golf_ball/data/','')))