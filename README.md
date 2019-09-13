# Tp1
Tp1 - Sistemas Embebidos

Primeros pasos en Git

Ir a la carpeta donde desean tener el repositorio.

1) Definir Usuario y email(opcional)

git config --global user.name "John Doe"

git config --global user.email johndoe@example.com

(Esto se hace una vez y nunca mas. La idea es que cada vez que suban va a aparecer que lo subio ese usuario)

2) Clonar el repo

Van a https://github.com/RamaVera/Tp1 se logean y buscan el boton de "Clone or Download"
Copian el link:
			https://github.com/RamaVera/Tp1
Van a la terminal y ejecutan

git clone https://github.com/RamaVera/Tp1

3) Se meten dentro de la carpeta

cd Tp1

Dentro de ahi van a ver los archivos del repo como este ! :)

4) Crear un branch (Leer completo antes de mandar a lo loco los comandos)

Para crear un branch es facil se usa el comando

git branch nombre_del_branch

Este comando crea la rama pero no los mueve a ella.
Si usan el comando sin el nombre del branch (solo git branch) les dira los branch que existen en su compu de manera LOCAL.
Si ejecutan git branch deberian solo ver al master con un asterisquito que les indica que estan en esa rama. 
Despues pueden crear el branch y volver a verificar que se creo que git branch, les aparecera el branch pero sin el asterisco
indicando que existe pero que no estas sobre el.

5) Movernos al branch.
Para movernos al branch en el git se usa el comando

git checkout nombre_del_branch 

Pueden usar el comando git branch y ver que ahora su branch tiene asterisquito. Si no hacen ningun cambio y tratan de subirlo al github no les creara nada
pero si agregan algun cambio, les creara la rama mas adelante cuando lo suban. Prueben crear algun archivo si quieren.
El comando git checkout sera el que nos ayudara a movernos por los nodos del git.

6) Una vez que uno esta en un branch, el branch es suyo y puede hacer lo que quieran. Los otros branch no se afectaran si se hacen cambios. Es como que se trabaja invisiblemente.

7) Para subir a la github son 3 pasos (si quieren ser mas profesionales pueden ser 5 usando un git status antes de hacer alguna de estas acciones para ver que estan aceptando o subiendo).

git add <archivos> (pueden usar git add . si son muchos OJO que esto acepta TOOODO ) 

este comando trackea los cambios, es decir, como que los acepta

git commit -m "nombre_del_commit"

este comando crea el nodo con los cambios aceptados por el add. Si trabajan con vi pueden usar 

git commit

que los lleva a Vi y ahi ponen el nombre (comandos utiles del vi: i <-- Insertar Text , ESC <-- Insertar Comando, En modo comando :wq  guarda y volves a la terminal)

Por ultimo se usa el push. Como primera y UNICA vez si uno esta en un branch o en cualquier lugar y quiere subir al repo tiene que usar el comando

git push -u origin nombre_del_branch

Despues de eso simplemente se usa el git push

8) Pueden ver como se crea el arbol en github.

Desde github dentro del repo busquen la pestaña Insigth y despues la opcion Network y flasheeen!! ajajaj

Cualquier duda pregunten.

Saludos Ramiro!! 


 





