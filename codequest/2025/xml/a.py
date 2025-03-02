import xml.etree.ElementTree as ET

t = int(input())

for _ in range(t):
    psize = int(input())
    xmlS = ""
    while True:
        line = input()
        xmlS += line
        xmlS += "\n"
        if line == "</parts>":
            break

    root = ET.fromstring(xmlS)
    partI = 1
    partIPrinted = False
    partS = 0
    name = None
    serial = None
    number = None

    for child in root:
        if len(child.attrib.keys()) == 0:
            name = child.find("name").text
            serial = child.find("serial").text
            number = child.find("number").text
            # print(child.tag, child.attrib, "empty!")
            # print(name, serial, number)
        else:
            if child.get("name"):
                name = child.get("name")
            if child.get("number"):
                number = child.get("number")
            if child.get("serial"):
                serial = child.get("serial")

            if child.text:
                serial = child.text

            # print("hi", child.keys())
            # for child1 in child:
            #     print("hello", child1)

        if name and serial and number:
            if not partIPrinted:
                print(partI)
                partIPrinted = True

            print(number + "," + serial + "," + name)
            partS += 1
            name = None
            child = None
            serial = None

            if partS == psize:
                partI += 1
                partS = 0
                partIPrinted = False
