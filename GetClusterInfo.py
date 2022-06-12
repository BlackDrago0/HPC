# Використовуючи команду pbsnodes та засоби обробки тексту UNIX (grep, sed, awk, wc, тощо) проаналізуйте характеристики обчислювальних вузлів кластера. Дайте відповіді на питання:
#
# Скільки робочих вузлів має кластер?
#
# Скільки є груп вузлів з однаковими характеристиками (кількість ядер, пам’яті)?
#
# Скільки в середньому гігабайт пам’яті на ядро має кластер?
#
# Скільки графічних прискорювачів встановлено на кластері?

import xml.dom.minidom as parser

doc = parser.parse('E:\\triod315\\5 курс\HPC\HPC\Lab1\Data.xml')

allDataCsv=''

# Woring nodes count
nodes=doc.getElementsByTagName('Node')
allCount=len(nodes)
workingCount=0
for node in nodes:
    stateValue=node.getElementsByTagName('state')[0].childNodes[0].nodeValue
    if node.getElementsByTagName('status')!=[]:
        allDataCsv=allDataCsv+f"\n"+node.getElementsByTagName('status')[0].childNodes[0].nodeValue
    if stateValue!='offline' and stateValue!='down' and stateValue!='state-unknown':
        workingCount+=1

print(allDataCsv)
print(f'Кількість робочих вузлів:\t {workingCount}')
print(f'Загальна кількість вузлів:\t {allCount}')
