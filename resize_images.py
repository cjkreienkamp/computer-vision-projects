import os
import glob
import cv2
import argparse

parser = argparse.ArgumentParser(
    description="Resize raw images to uniformed target size."
)
parser.add_argument(
    "--project-dir",
    help="Directory name of the project.",
    default="./project_name",
    type=str,
)
parser.add_argument(
    "--target-size",
    help="Target size to resize as a tuple of 2 integers.",
    default="(800, 600)",
    type=str,
)
args = parser.parse_args()

project_dir = args.project_dir
raw_dir = os.path.join(project_dir, "raw_images")
save_dir = os.path.join(project_dir, "data")
ext = 'jpg'
target_size = eval(args.target_size)
msg = "--target-size must be a tuple of 2 integers"
assert isinstance(target_size, tuple) and len(target_size) == 2, msg
raw_images = glob.glob(os.path.join(raw_dir, f'*.{ext}'))
os.makedirs(save_dir, exist_ok=True)
print(f"{len(raw_images)} files to resize from directory '{raw_dir}' to target size:{target_size}")
for i, raw_fname in enumerate(raw_images):
    print(".", end="", flush=True)
    raw_image = cv2.imread(raw_fname)
    resized_image = cv2.resize(raw_image, target_size)
    resized_fname = os.path.join(save_dir, f'{i}.{ext}')
    cv2.imwrite(resized_fname, resized_image)
print(f"\nDone resizing {len(raw_images)} files.\nSaved to directory: `{save_dir}`")