DELETE FROM Postea;
DELETE FROM Compra;
DELETE FROM Articulo;
DELETE FROM Usuario; 

INSERT INTO Usuario(Usuario, Contrasena, Nombre, Email, Telefono) VALUES
		('1', 'yisuspassword', 'Jesus Casasola', 'jesus.casasola@ucr.ac.cr', '11111111' ),
		('2', 'luchopassword', 'Lucho Ramirez', 'lucho.ramirez@ucr.ac.cr', '22222222' ),
		('3', 'davidpassword', 'David', 'david@ucr.ac.cr', '33333333'),
		('4', 'isaccpassword', 'Isacc Zúñiga', 'isacc.zuniga@ucr.ac.cr', '44444444');

/*
    Articulo.Estado:
	0 -> disponible
	1 -> enCarrito
	2 -> eliminado/comprado
*/
INSERT INTO  Articulo(Usuario_D, Nombre, Tipo, Costo, Descripcion, Estado) VALUES
		('1', 'iphoneX', 'Celular', 600000, 'Celular dos meses de uso', '0'),
		('2', 'dell', 'Computadora', 700000, 'Computadora dell nueva', '0'),
		('3', 'Samsung monitor', 'Screen', 100000, 'Monitor de 28 pulgadas relativamente nuevo', '0'),
		('4', 'Torre computadora','Desktop', 100000, 'Case para motherboard X nuevo', '0'),
		('1', 'Xbox One', 'Consola', 666000, 'Consola en excelente estado', '0');


INSERT INTO  Postea(Usuario, ID, Fecha) VALUES
		('1', '1', '2020-02-01'),
		('2','2','2020-03-02'),
		('3','3','2020-04-03'),
		('4','4','2020-05-04'),
		('1','5','2020-05-06');


INSERT INTO Compra(Usuario, ID, Fecha) VALUES
		('1','2','2020-02-01'),
		('2','1','2020-07-06'),
		('3','4','2020-07-08'),
		('4','3','2020-09-08');

