# Modulo Distancia
Modulo de distancia usando un Arduino Nano y el sensor VL53Lxx-v2

## Libreria necesaria
Para instalar la librería correcta para el módulo de distancia VL53Lxx-v2 es necesario ir al "Gestor de Liberias" en el IDE de Arduino y escribir en el buscador "vl53l1x", apareceran las siguientes opciones:

![image](https://user-images.githubusercontent.com/50645020/121561904-f0876c00-c9e6-11eb-85e9-87958a08d925.png)

La libreria que debe instalarse es la tercera, llamada "SparkFun VL53L1X 4m Laser Distance Sensor", una vez ya instalada, encontrarás en el apartado de ejemplos, carpeta "SparkFun VL53L1X 4m Laser Distance Sensor" una serie de códigos listos para ejecutar, uno de ellos es el archivo "Example1_ReadDistance.ino" que permite leer la distancia y los imprime en consola en mm.

Si se descarga el archivo adjuntado en el GitHub debería funcionar todo correctamente.

**NOTA: Una cosa a tener en cuenta al cargar código al arduino nano específico usado en este proyecto es que en "Herramientas" del IDE de arduino, hay que ir a la opción de procesador y elegir la opción "ATmega328P (Old Bootloader)". De esta forma no habrá ningún problema.**

## Esquema de conexiones

![schematicDistance](https://user-images.githubusercontent.com/50645020/121569677-09941b00-c9ef-11eb-9f6e-2fb289564962.png)

Teniendo en consideración el siguiente Layout de pines para Arduino Nano

![image](https://user-images.githubusercontent.com/50645020/121569833-36483280-c9ef-11eb-97bc-84c8949436bf.png)





