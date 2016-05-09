## Директория с HLS ядрами

### Создание ядер

* В в каждой папке есть create_project.tcl - скрипт, содающий Vivado HLS проект и синтезирующий С код
	
* После работы стрипта будет создано IP ядро в папке
  * hls\$Core_name\$HLS_Project_name\solution1\impl\ip	
  * которое надо подцепить в Vivado как user repository
  * Для запуска create_project.tcl под Windwos есть файл create_project.bat, в нем надо поправить путь к Vivado HLS