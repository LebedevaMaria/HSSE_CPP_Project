# HSSE_CPP_Project
Отличия между std::string и qString:
1. В qString для хранения строк используется UTF-16, а в std::string используется UTF-8.
2. Обычно qString медленней чем std::string.
3. Для qString есть методы для конвертации в std::string и обратно. В std::string таких методов нет.
4. Обычно  qString требует больше памяти чем std::string.
5. В qString более широкий набор методов.
