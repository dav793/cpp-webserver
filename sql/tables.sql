CREATE TABLE Usuario(
    Usuario     VARCHAR(15)     NOT NULL,
    Contrasena  VARCHAR(20)     NOT NULL,
    Nombre      VARCHAR(30)     NOT NULL,
    Email       VARCHAR(30)     NOT NULL,
    Telefono    CHAR(8)                 ,
    PRIMARY KEY (Usuario)        
);

CREATE TABLE Articulo(
    ID          INT             NOT NULL AUTO_INCREMENT,
    Usuario_D   VARCHAR(15)     NOT NULL,
    Nombre      VARCHAR(50)     NOT NULL,
    Tipo        VARCHAR(50)     NOT NULL,
    Costo       FLOAT           NOT NULL,
    Descripcion VARCHAR(250)            ,
    Estado      INT             NOT NULL,
    PRIMARY KEY (ID), 
    FOREIGN KEY(Usuario_D) REFERENCES Usuario (Usuario) ON DELETE CASCADE   
);

CREATE TABLE Formulario(
    ID          INT             NOT NULL AUTO_INCREMENT,
    Usuario_D   VARCHAR(15)     NOT NULL,
    Tipo        VARCHAR(10)     NOT NULL,
    Cuerpo      VARCHAR(500)    NOT NULL,
    PRIMARY KEY (ID),
    FOREIGN KEY(Usuario_D) REFERENCES Usuario (Usuario) ON DELETE CASCADE
);

CREATE TABLE Compra(
    Usuario     VARCHAR(15)     NOT NULL,
    ID          INT             NOT NULL,
    Fecha       date            NOT NULL,
    PRIMARY KEY (Usuario, ID)           ,
    FOREIGN KEY(Usuario) REFERENCES Usuario (Usuario) ON DELETE NO ACTION,
    FOREIGN KEY(ID) REFERENCES Articulo (ID) ON DELETE NO ACTION
);

CREATE TABLE Postea(
    Usuario     VARCHAR(15)     NOT NULL,
    ID          INT             NOT NULL,
    Fecha       date            NOT NULL,
    PRIMARY KEY (Usuario, ID)           ,
    FOREIGN KEY(Usuario) REFERENCES Usuario (Usuario) ON DELETE NO ACTION,
    FOREIGN KEY(ID) REFERENCES Articulo (ID) ON DELETE NO ACTION
);

CREATE TABLE Envia(
    Usuario     VARCHAR(15)     NOT NULL,
    ID          INT             NOT NULL,
    Fecha       date            NOT NULL,
    PRIMARY KEY (Usuario, ID)           ,
    FOREIGN KEY(Usuario) REFERENCES Usuario (Usuario) ON DELETE NO ACTION,
    FOREIGN KEY(ID) REFERENCES Formulario (ID) ON DELETE NO ACTION
);

CREATE TABLE Carrito(
    UsuarioComprador     VARCHAR(15)     NOT NULL,
    IDArticulo           INT             NOT NULL,
    Fecha                date            NOT NULL,
    PRIMARY KEY (UsuarioComprador, IDArticulo)           ,
    FOREIGN KEY(UsuarioComprador) REFERENCES Usuario (Usuario) ON DELETE NO ACTION,
    FOREIGN KEY(IDArticulo) REFERENCES Articulo (ID) ON DELETE NO ACTION
);