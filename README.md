
# Sitio de E-commerce
## Proyecto de curso de Seguridad de Sistemas Computacionales de la Universidad de Costa Rica

## Configuraci?n del proyecto

1. En el root del proyecto, cree la carpeta `/bin`.

2. Copie `Makefile.template` y nombrelo `Makefile`.

3. Entre a `Makefile` y sustituya las rutas en los comandos por la ruta que corresponde al directorio ra?z del proyecto en su ambiente local.

4. Vaya a `/config`, copie `config.template` y nombrelo `config`.

5. Entre a `/config/config` y sustituya los valores de las variables de configuraci?n por las correspondientes en su ambiente.

## Configuraci?n de Apache

En `httpd.conf`, hacer lo siguiente:

1. Definir la ruta local del proyecto agregando la siguiente l?nea al inicio (cambiar la ruta por la que corresponde al directorio ra?z del proyecto en su ambiente local):
	```
	Define PROJECTROOT "C:/.../proyecto"
	```

2. Asegurarse que la siguiente l?nea existe y NO est? comentada:
	```
	LoadModule cgi_module modules/mod_cgi.so
	```

3.  Cambiar esta parte:
	```
	<IfModule dir_module>
        DirectoryIndex index.html
    </IfModule>
	```
	por esto:
	```
	<IfModule dir_module>
        DirectoryIndex /store/webserver.cgi index.html
    </IfModule>
	```

4. Comentar esta l?nea:
	```
	# ScriptAlias /cgi-bin/ "${SRVROOT}/cgi-bin/"
	```

5. Agregar estas l?neas:
	```
	ScriptAlias /store/ "${PROJECTROOT}/bin/"
	Alias /css/ "${PROJECTROOT}/public/css/"
    Alias /js/ "${PROJECTROOT}/public/js/"
    Alias /assets/ "${PROJECTROOT}/public/assets/"
	```

6. Cambiar esta parte:
	```
	<Directory "${SRVROOT}/cgi-bin">
		AllowOverride None
		Options None
		Require all granted
	</Directory>
	```
	por todo esto:
	```
	<Directory "${PROJECTROOT}/bin/">
		AllowOverride None
		Options +ExecCGI -MultiViews +SymLinksIfOwnerMatch
		Require all granted
	</Directory>

	<Directory "${PROJECTROOT}/public/css/">
		AllowOverride None
		Options Indexes FollowSymLinks
		Require all granted
	</Directory>

	<Directory "${PROJECTROOT}/public/js/">
		AllowOverride None
		Options Indexes FollowSymLinks
		Require all granted
	</Directory>

	<Directory "${PROJECTROOT}/public/assets/">
		AllowOverride None
		Options Indexes FollowSymLinks
		Require all granted
	</Directory>
	```

## Compilaci?n y ejecuci?n

### Ambiente de produccion

1. Con Apache corriendo, ejecute el siguiente comando:
	```
	make
	```

2. Desde el browser, entre a la siguiente URL:
	```
	localhost
	```

### Ambiente de desarrollo (sin Apache)

1. Ejecute el siguiente comando:
	```
	make build-dev
	```

2. Desde `<PROJECT_ROOT>/bin`, ejecute el siguiente comando:
	```
	./webserver
	```

## Probar solicitudes

### POST : Registrar un usuario

```
curl -i -d "name=David&username=dvargas&password=1234" -H "Content-Type: application/x-www-form-urlencoded" -X POST http://localhost:80/store/register.cgi
```

### POST : Login

```
curl -i -d "username=dvargas&password=1234" -H "Content-Type: application/x-www-form-urlencoded" -X POST http://localhost:80/store/login.cgi
```

## DB

### Crear base de datos y usuario

1. Entrar como `root`:
	```
	mysql -u root -p
	```

2. Crear usuario `dbuser` con password `comprayventa`:
	```
	CREATE USER 'dbuser'@'localhost' identified by 'comprayventa';
	GRANT ALL PRIVILEGES ON *.* TO 'dbuser'@'localhost';
	FLUSH PRIVILEGES;
	```

3. Crear base de datos `comprayventa`:
	```
	CREATE DATABASE comprayventa;
	```

4. Importar base de datos de archivos:
	```
	mysql -u dbuser -p comprayventa < sql/drop.sql
	mysql -u dbuser -p comprayventa < sql/tables.sql
	mysql -u dbuser -p comprayventa < sql/data.sql
	```

### Imprimir tuplas de tabla `Usuario`:

1. Entrar como usuario `dbuser`:
	```
	mysql -u dbuser -p comprayventa
	```

2. Imprimir tuplas:
	```
	SELECT * FROM comprayventa;
	```
