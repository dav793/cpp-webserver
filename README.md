
# Sitio de E-commerce
## Proyecto de curso de Seguridad de Sistemas Computacionales de la Universidad de Costa Rica

## Configuración del proyecto

1. Vaya a `/config`, copie `config.template` y nombrelo `config`.

2. Entre a `/config/config` y sustituya los valores de las variables de configuración por las correspondientes en su ambiente.

## Configuración de Apache

En `httpd.conf`, hacer lo siguiente:

1. Definir la ruta local del proyecto agregando la siguiente línea al inicio (cambiar la ruta por la que corresponde al directorio raíz del proyecto en su ambiente local):
	```
	Define PROJECTROOT "C:/.../proyecto"
	```

2. Asegurarse que la siguiente línea existe y NO está comentada:
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

4. Comentar esta línea:
	```
	# ScriptAlias /cgi-bin/ "${SRVROOT}/cgi-bin/"
	```

5. Agregar estas líneas:
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

## Compilación y ejecución

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
