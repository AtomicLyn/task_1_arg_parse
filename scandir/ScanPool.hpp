#pragma once

#include "Directory.hpp"
#include <filesystem>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace scan_dir {
	/// @brief Класс пула для многопоточной обработки директории
	class ScanPool {
		std::string mainPath; ///< Поле, хранящее путь до главной директории 
		int poolSize; ///< Поле, хранящее количество потоков в пуле
		/** @brief Поле, хранящее значение в микросекундах, на сколько усыпить первый поток в первом цикле
		* Используется, чтобы дать возможность остальным потокам запуститься и начать обход директории. 
		* В противном случае первый поток имеет крайне высокий шанс выполнить обход всех поддиректориий еще до запуска всех потоков
		*/
		std::chrono::microseconds debugSleep; 

		Directory mainDirectory; ///< Поле, хранящее объект главной директории	
		/** @brief Поле, хранящее очередь из ссылок на поддиректории
		* Сихнронизируется между потоками при помощи связки мьютекс (tasksM) + условная переменная (tasksCV)
		*/ 
		std::queue<std::reference_wrapper<Directory>> tasks; 
		std::mutex tasksM; ///< Мьютекс для очереди tasks
		std::condition_variable tasksCV; ///< Условная переменная для очереди tasks

		std::vector<std::thread> threads; ///< Поле, хранящее все запущенные потоки


		std::mutex poolM; ///< Мьютекс для пула
		/** @brief Условная переменная для пула
		* Используется для ожидания пулом сообщения о завершении работ всех потоков
		*/
		std::condition_variable poolCV; 

		bool isDone = false; ///< Поле, хранящее флаг для завершения всех потоков

		/** @brief Метод для обхода директории потоком
		* Выполняет получение ссылки на директорию для обхода, после чего заполняет директорию id потока, файлами и поддиректориями.
		* При нахождении поддиректории добавляет ее в очередь tasks. Прекращает работу при флаге isDone = true.
		* @param[in] isWorking Флаг для указания пулу, что поток в данный момент выполняет обход директории
		* @param[in] needToSleep Флаг для первого потока, указывающий, что потоку нужно заснуть на время debugSleep.
		* Выполняется один раз, после чего флаг переходит в состояние false.
		*/
		void Scan(bool& isWorking, bool needToSleep = false);

	public:
		ScanPool(std::string mainPath, int poolSize, std::chrono::microseconds debugSleep);
		~ScanPool();
		/** @brief Метод для запуска многопоточного обхода директории по пути mainPath
		* Задает объект mainDirectory, который добавляется в очередь tasks. 
		* Запускает количество потоков, равное poolSize. Для первого потока указывается флаг для debugSleep.
		* Ожидает завершения работ всех потоков.
		* @attention Блокирует основной поток в main до завершения обхода директории
		* @return Константную ссылку на главную директорию mainDirectory
		*/
		const Directory& StartAndGetDirectory();

	};
}