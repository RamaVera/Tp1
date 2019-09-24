IMPORTANTE LOS BRANCHES SE BORRAN LUEGO DE MERGEAR!! 
Deben borrarlos:
1) se mueven al master con git checkout master
2) borran el branch con git branch -d <NombreDelBranch>
3) meten git pull origin master para traer los datos

Recuerden antes de hacer nada, hagan un "git log" y chequeen que la historia de su repo (LOCAL) coincide con el de la historia del github (REMOTO)
Si ven que es diferente hagan un "git pull"!!!

En el peor de los casos siempre se puede borrar la carpeta Tp1 y volver a ejecutar el git clone pues los cambios son locales hasta que se sube al repoo
