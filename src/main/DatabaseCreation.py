'''
Created on 10.03.2010

@author: jan
'''

import sqlite3


if __name__ == '__main__':
    
    cursor = sqlite3.connect("testdatenbank.db").cursor()
    
    sql = """CREATE TABLE konto (
        id INTEGER, name TEXT, uid INTEGER
    )"""
    cursor.execute(sql)
    
    sql = """CREATE TABLE ware (
        id INTEGER, name TEXT, preis REAL, bestand INTEGER
    )"""
    cursor.execute(sql)
    
    pass
