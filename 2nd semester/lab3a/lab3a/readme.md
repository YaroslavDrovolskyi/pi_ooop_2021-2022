# **Лабораторна робота №3а**  
## Виконав Дровольський Ярослав, К-29  
Я реалізував послідовні та мультипоточні версії таких алгоритмів:
- алгоримтм Штрассена для множення матриць; 
- алгоритм сортування QuickSort.

При реаліації цих алгоритмів було використано патерн **Template method**: основна логіка ("кістяк") алгоритму описується в базовому класі, а місця, в яких послідовний та мультипоточний алгоритми відрізняються, перевизначаються у відповідних підкласах. Наприклад, вся основна логіка для quicksort визначається в базовому класі `QuickSort`. А послідовній / мультипоточній версіям треба override лише один метод: `runSortImplForSubarrays()`.

Також було реалізовано **unit tests**, які перевіряють коректність роботи алгоримтів як при правильних, так і при неправильних вхідних даних.

Окрім цього, було реалізовано **bencmark-режим**, який тестує алгоритми при різному розмірі вхідних даних. Для QuickSort вимірюється час роботи для випадкових, майже впорядкованих, та відсортованих у зворотньому порядку масивів. Результати benchmark'ів знаходяться у файлах `multiplication_bechmark.txt` та `benchmark_quicksort.txt`.

З результів вимірів часу роботи видно, що мультипоточний алгоритм Штрассена працює приблизно в 4 рази швидше, ніж послідовний.

Документація знаходиться в папці `/docs`.