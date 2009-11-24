#!/usr/bin/env python

import sqlalchemy
from sqlalchemy import create_engine
from sqlalchemy import Table, Column, Integer, String, MetaData, ForeignKey
from sqlalchemy.orm import mapper
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker
from sqlalchemy.orm import relation, backref

Base = declarative_base()

class User(Base):
	__tablename__ = 'users'

	id = Column(Integer, primary_key=True)
	name = Column(String)
	fullname = Column(String)
	password = Column(String)
	
	# addresses = relation('Address', order_by = "Address.id", backref="user")

	def __init__(self, name, fullname, password):
		self.name = name
		self.fullname = fullname
		self.password = password

	def __repr__(self):
		return ("<User('%s', '%s', '%s')>" % (self.name, self.fullname, self.password))

class Address(Base):
    __tablename__ = 'address'
    id = Column(Integer, primary_key = True)
    email_address = Column(String, nullable = False)
    user_id = Column(Integer, ForeignKey('users.id'))
    
    user = relation(User, backref=backref('addresses', order_by=id))
    
    def __init__(self, email_address):
        self.email_address = email_address
        
    def __repr__(self):
        return "<Address('%s')>" % self.email_address

def TestUser(users_table):
	ed_user = User(u'ed', u'Ed Jones', u'edspassword')
	print ('ed_user.name: %s' % ed_user.name)

def CreateTable(engine):
	metadata = MetaData()
	users_table = Table('users', metadata,
						Column('id', Integer, primary_key=True),
						Column('name', String(20)),
						Column('fullname', String(50)),
						Column('password', String(20)))
	metadata.create_all(engine)

	return users_table

def main():
	print ('sqlalchemy.version(%s)' % sqlalchemy.__version__)
	engine = create_engine('sqlite:///test.db', echo=True)
	Session = sessionmaker(bind=engine)
	session = Session()

	ed_user = User('ed', 'Ed Jones', 'edspassword')
	session.add(ed_user)
	
	session.add_all([
		User('wendy', 'Wendy Williams', 'foobar'),
		User('mary', 'Mary Contrary', 'xxg527'),
		User('fred', 'Fred Flinstone', 'blah')])
	
	for instance in session.query(User).order_by(User.id):
		print instance.name, instance.fullname
		instance.addresses = [Address('%s@google.com' % instance.name),
							  Address('%s@google.com' % instance.name)]

	session.commit()
	'''
	users_table = CreateTable(engine)
	TestUser(users_table)
	'''

if __name__ == '__main__':
	main()
