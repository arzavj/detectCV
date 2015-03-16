import tarfile
import urllib
import os
import argparse

pwd = os.path.abspath(os.path.dirname(__file__))
tmp_folder = pwd + '/../tmp/'
tmp_tars = tmp_folder + 'tarfiles/'
base_image_url = "http://www.image-net.org/download/synset?wnid=%s&username=%s&accesskey=%s&release=latest&src=stanford"
base_mapping_url = "http://www.image-net.org/api/text/imagenet.synset.geturls.getmapping?wnid=%s"
label_wnids = {
    'bike': ['n02834778', 'n03792782', 'n03853924', 'n04126066'],
    'bus': ['n04212165', 'n04146614'],
    'truck': ['n03256166', 'n03417042', 'n04467665'],
    'skateboard': ['n04225987'],
    'stroller': ['n02766534'],
    'car': ['n02958343']
}

def download_images(wnid):
    url = base_image_url % wnid
    local_filename = tmp_tars + wnid + '.tar'
    try:
        urllib.urlretrieve(url, local_filename)
    except Exception,e:
        print "Error downloading tar file at url: %s" % url
        print e
        return
     
    # tar file path to extract
    extractTarPath = tmp_folder
     
    # open the tar file
    tfile = tarfile.open(local_filename)
     
    if tarfile.is_tarfile(local_filename):
        # extract all contents
        tfile.extractall(extractTarPath)
    else:
        print local_filename + " is not a tarfile."

def download_mappings(wnid, label):
    url = base_mapping_url % wnid
    local_filename = pwd + '/' + label + '_' + wnid + '_imageurls.txt'
    try:
        urllib.urlretrieve(url, local_filename)
    except Exception,e:
        print "Error downloading mappings file at url: %s" % url
        print e

def main(args):
    for label, wnids in label_wnids.items():
        for wnid in wnids:
            if args.images:
                download_images(wnid)
            if args.mappings:
                download_mappings(wnid, label)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--images", help="download imagenet images",
                    action="store_true")
    parser.add_argument("-m", "--mappings", help="download image url mappings",
                    action="store_true")
    args = parser.parse_args()
    main(args)
