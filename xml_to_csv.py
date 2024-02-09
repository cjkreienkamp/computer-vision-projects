import os
import glob
import pandas as pd
import argparse
import xml.etree.ElementTree as ET


def xml_to_csv(path):
    classes_names = []
    xml_list = []
    for xml_file in glob.glob(path + "/*.xml"):
        tree = ET.parse(xml_file)
        root = tree.getroot()
        for member in root.findall("object"):
            classes_names.append(member[0].text)
            value = (
                root.find("filename").text,
                int(root.find("size")[0].text),
                int(root.find("size")[1].text),
                member[0].text,
                int(member[4][0].text),
                int(member[4][1].text),
                int(member[4][2].text),
                int(member[4][3].text),
            )
            xml_list.append(value)
    column_name = [
        "filename",
        "width",
        "height",
        "class",
        "xmin",
        "ymin",
        "xmax",
        "ymax",
    ]
    xml_data_frame = pd.DataFrame(xml_list, columns=column_name)
    classes_names = list(set(classes_names))
    classes_names.sort()
    return xml_data_frame, classes_names


parser = argparse.ArgumentParser(
    description="Sample TensorFlow XML-to-CSV converter"
)
parser.add_argument(
    "--project-dir",
    help="Directory name of the project.",
    default="./project_name",
    type=str,
)
args = parser.parse_args()

project_dir = args.project_dir
train_xml_dir = os.path.join(project_dir,'data','train')
test_xml_dir = os.path.join(project_dir,'data','test')
train_labels_csv_file = os.path.join(project_dir,'annotations','train_labels.csv')
test_labels_csv_file = os.path.join(project_dir,'annotations','test_labels.csv')
os.makedirs(os.path.dirname(train_labels_csv_file), exist_ok=True)
os.makedirs(os.path.dirname(test_labels_csv_file), exist_ok=True)
train_xml_data_frame, train_classes_names = xml_to_csv(train_xml_dir)
test_xml_data_frame, test_classes_names = xml_to_csv(test_xml_dir)

train_xml_data_frame.to_csv(train_labels_csv_file, index=None)
test_xml_data_frame.to_csv(test_labels_csv_file, index=None)

label_map_path = os.path.join(project_dir, 'annotations', 'label_map.pbtxt')
pbtxt_content = ''
classes_names = train_classes_names
classes_names.extend(class_name for class_name in test_classes_names if class_name not in train_classes_names)
for i, class_name in enumerate(classes_names):
    pbtxt_content = (pbtxt_content
        + "item {{\n    id: {0}\n    name: '{1}'\n}}\n\n".format(
            i + 1, class_name
        )
    )
pbtxt_content = pbtxt_content.strip()
with open(label_map_path, "w") as f:
    f.write(pbtxt_content)