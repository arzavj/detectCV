
import cv2
import urllib
import sys, os
import xml.etree.ElementTree as ET

pwd = os.path.abspath(os.path.dirname(__file__))
image_dir_name = pwd + '/../images/'
tmp_folder = pwd + '/../tmp/'

if __name__ == '__main__':

    for x in os.walk(pwd):
        if (x[0] != pwd):
            label = x[0].split('/')[-1]
            print 'Writing bbox images for %s' % label

            image_urls_mapping = {}
            with open(label + "_imageurls.txt") as f:
                for line in f:
                    if line.strip():
                        (key, val) = line.split()
                        image_urls_mapping[key] = val

            print 'Image URL mapping created for %s' % label

            count = 0
            for xml_filename in x[2]:
                if not xml_filename.endswith('.xml'): continue
                tree = ET.parse(label + '/' + xml_filename)
                root = tree.getroot()
                filename = root.findall('./filename')[0].text
                local_filename = tmp_folder + '%s.JPEG' % filename
                img = cv2.imread(local_filename)
                if img is None:
                    url = image_urls_mapping.get(filename)
                    if url is not None:
                        try:
                            urllib.urlretrieve(url, local_filename)
                            img = cv2.imread(local_filename)
                        except Exception,e:
                            print "Error downloading image file at url: %s" % url
                            print e

                if img is not None:
                    xmin = int(root.findall('./object/bndbox/xmin')[0].text)
                    ymin = int(root.findall('./object/bndbox/ymin')[0].text)
                    xmax = int(root.findall('./object/bndbox/xmax')[0].text)
                    ymax = int(root.findall('./object/bndbox/ymax')[0].text)

                    count = count + 1
                    bbox_img = img[ymin:ymax, xmin:xmax]
                    bbox_filename = image_dir_name + label + '_' + filename + "_bbox.jpg"
                    cv2.imwrite(bbox_filename, bbox_img)
                    if count % 50 == 0:
                        print '%s bbox images downloaded so far' % str(count)
                else:
                    print local_filename + ' could not be read'

    print 'Done'
    print 'You can now delete the folder %s' % tmp_folder


