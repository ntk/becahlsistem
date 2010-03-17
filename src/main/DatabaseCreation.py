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
    
    sql = """ SELECT * FROM ? WHERE id = ?"""
    werte = ("konto", 5)
    cursor.execute(sql, werte)
    daten = cursor.fetchone()
    
    sql = """CREATE TABLE bezahlvorgang (
        kontoid INTEGER, wareid INTEGER, anzahl INTEGER
    )"""
    cursor.execute(sql)
    
    #test..
   
    
    
    
    pass