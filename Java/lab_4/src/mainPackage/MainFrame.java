package mainPackage;

import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;

import javax.swing.*;


@SuppressWarnings("serial")
public class MainFrame extends JFrame {

    private static final int WIDTH = 700;
    private static final int HEIGHT = 500;

    // Объект диалогового окна для выбора файлов.
    private JFileChooser fileChooser = null;

    // Элементы меню вынесены в поля данных класса, так как ими необходимо
    // манипулировать из разных мест
    private JMenuItem saveToTextMenuItem;
    private JMenuItem searchValueMenuItem;
    private JMenuItem infoP;
    // Поля ввода для считывания значений переменных
    private JTextField textFieldFrom;
    private JTextField textFieldTo;
    private JTextField textFieldStep;
    private JTextField textFieldParam;
    private Box hBoxResult; //
    // Визуализатор ячеек таблицы
    private FunctionTableCellRenderer renderer = new FunctionTableCellRenderer();
    private mainPackage.FunctionTableModel data;  // модель данных с результами вычислений

    public MainFrame() {
        super("Tabulating a function on a segment"); // Обязательный вызов конструктора предка
        setSize(WIDTH, HEIGHT);// Установить размеры окна
        Toolkit kit = Toolkit.getDefaultToolkit();
        setLocation((kit.getScreenSize().width - WIDTH)/2, // Отцентрировать окно приложения на экране
                (kit.getScreenSize().height - HEIGHT)/2);

        JMenuBar menuBar = new JMenuBar();  //Создать полосу меню и установить ее в верхнюю часть фрейма
        setJMenuBar(menuBar);
        JMenu fileMenu = new JMenu("File");
        menuBar.add(fileMenu);
        JMenu tableMenu = new JMenu("Table");
        menuBar.add(tableMenu);
        JMenu referenceMenu = new JMenu("Reference");
        menuBar.add(referenceMenu);

        // Создать новое "действие" по сохранению в текстовый файл
        Action saveToTextAction = new AbstractAction(
                "Save to text file") {
            public void actionPerformed(ActionEvent event) {
                // Если экземпляр диалогового окна "Открыть файл" еще не создан,
                // то создать его и инициализировать текущей директорией
                if (fileChooser==null) {
                    fileChooser = new JFileChooser();
                    fileChooser.setCurrentDirectory(new File("."));
                }

                // Показать диалоговое окно
                if (fileChooser.showSaveDialog(MainFrame.this) ==
                        JFileChooser.APPROVE_OPTION)
                    saveToTextFile(fileChooser.getSelectedFile());
            }
        };
        saveToTextMenuItem = fileMenu.add(saveToTextAction);
        saveToTextMenuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.getExtendedKeyCodeForChar('S'),
                InputEvent.CTRL_DOWN_MASK));
        saveToTextMenuItem.setEnabled(false);

        // Создать новое действие по поиску значений функции
        Action searchValueAction = new AbstractAction("Find the value of a function") {
            public void actionPerformed(ActionEvent event) {
                // Запросить пользователя ввести искомую строку
                String value = JOptionPane.showInputDialog(MainFrame.this,
                        "Enter a value to search", "Finding a value",
                        JOptionPane.QUESTION_MESSAGE);
                // Установить введенное значение в качестве иголки
                renderer.setNeedle(value);
                // Обновить таблицу
                getContentPane().repaint();
            }
        };

        Action showP = new AbstractAction(
                "Show P") {
            public void actionPerformed(ActionEvent event) {
                Double param = Double.parseDouble(textFieldParam.getText());
                JLabel info = new JLabel("Parametr P: " + param);
                JOptionPane.showMessageDialog(MainFrame.this, info,
                        "Info about P", JOptionPane.PLAIN_MESSAGE);

            }
        };
        searchValueMenuItem = tableMenu.add(searchValueAction);
        infoP = tableMenu.add(showP);
        searchValueMenuItem.setEnabled(true);
        searchValueMenuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.getExtendedKeyCodeForChar('F'),
                InputEvent.CTRL_DOWN_MASK));
        searchValueMenuItem.setEnabled(false);



        Action aboutProgrammAction = new AbstractAction("About the program") {
            public void actionPerformed(ActionEvent event) {
                JLabel info = new JLabel("Work done by Artur Lynko, 2 course 4 group");
                JOptionPane.showMessageDialog(MainFrame.this, info,
                        "About the program", JOptionPane.PLAIN_MESSAGE);
            }
        };

        referenceMenu.add(aboutProgrammAction);


        textFieldFrom = new JTextField("0.0", 10);
        // Установить максимальный размер равный предпочтительному, чтобы
        // предотвратить увеличение размера поля ввода
        textFieldFrom.setMaximumSize(textFieldFrom.getPreferredSize());

        textFieldTo = new JTextField("1.0", 10);
        textFieldTo.setMaximumSize(textFieldTo.getPreferredSize());

        // Создать поле для ввода шага по X
        textFieldStep = new JTextField("0.1", 10);
        textFieldStep.setMaximumSize(textFieldStep.getPreferredSize());


        textFieldParam= new JTextField("0.0", 10);
        textFieldParam.setMaximumSize(textFieldParam.getPreferredSize());

        // Создать контейнер типа "коробка с горизонтальной укладкой"
        Box hboxXRange = Box.createHorizontalBox();
        //hboxXRange.setBorder(BorderFactory.createTitledBorder(
          //      BorderFactory.createEtchedBorder(), "Настройки:"));


        hboxXRange.add(Box.createHorizontalGlue());
        hboxXRange.add(new JLabel("X initial:"));
        hboxXRange.add(Box.createHorizontalStrut(10));
        hboxXRange.add(textFieldFrom);
        hboxXRange.add(Box.createHorizontalStrut(20));
        hboxXRange.add(new JLabel("X final:"));
        hboxXRange.add(Box.createHorizontalStrut(10));
        hboxXRange.add(textFieldTo);
        hboxXRange.add(Box.createHorizontalStrut(20));
        hboxXRange.add(new JLabel("Step for X:"));
        hboxXRange.add(Box.createHorizontalStrut(10));
        hboxXRange.add(textFieldStep);
        hboxXRange.add(Box.createHorizontalStrut(20));
        hboxXRange.add(new JLabel("Reduced for Y (P): "));
        hboxXRange.add(Box.createHorizontalStrut(10));
        hboxXRange.add(textFieldParam);
        hboxXRange.add(Box.createHorizontalGlue());

        Box Formula = Box.createHorizontalBox();
        Formula.add(Box.createHorizontalGlue());
        JLabel F = new JLabel("Formula:  Y = P - X ");
        Formula.add(F);
        Formula.add(Box.createHorizontalGlue());



/*
        Box Param = Box.createHorizontalBox();
        Param.add(Box.createHorizontalGlue());
        Param.add(new JLabel("Reduced for Y (P): "));
        Param.add(Box.createHorizontalStrut(10));
        Param.add(textFieldParam);
        Param.add(Box.createHorizontalGlue());

 */

        Box settings = Box.createVerticalBox();
        settings.setBorder(BorderFactory.createTitledBorder(
                     BorderFactory.createEtchedBorder(), "Settings:"));
        settings.add(Box.createVerticalGlue());
        settings.add(hboxXRange);
        settings.add(Box.createVerticalStrut(20));
        settings.add(Formula);
        //settings.add(Box.createHorizontalStrut(20));
        //settings.add(Param);
        settings.add(Box.createVerticalGlue());

        // Установить предпочтительный размер области больше
        // минимального, чтобы при  компоновке область совсем не сдавили
        settings.setPreferredSize(new Dimension(
                new Double(settings.getMaximumSize().getWidth()).intValue(),
                new Double(settings.getMinimumSize().getHeight()*1.5).intValue()));
        // Установить область в верхнюю (северную) часть компоновки
        getContentPane().add(settings, BorderLayout.NORTH);

        // Создать кнопку "Вычислить"
        JButton buttonCalc = new JButton("Calculate");
        buttonCalc.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent ev) {
                try {
                    // Считать значения начала и конца отрезка, шага
                    Double from = Double.parseDouble(textFieldFrom.getText());
                    Double to = Double.parseDouble(textFieldTo.getText());
                    Double step = Double.parseDouble(textFieldStep.getText());
                    Double param = Double.parseDouble(textFieldParam.getText());

                    // На основе считанных данных создать экземпляр модели таблицы
                    data = new mainPackage.FunctionTableModel(from, to, step, param);
                    // Создать новый экземпляр таблицы
                    JTable table = new JTable(data);
                    // Установить в качестве визуализатора ячеек для класса Double
                    //разработанный визуализатор
                    table.setDefaultRenderer(Double.class, renderer);
                    // Установить размер строки таблицы в 30 пикселов
                    table.setRowHeight(30);
                    // Удалить все вложенные элементы из контейнера hBoxResult
                    hBoxResult.removeAll();
                    // Добавить в hBoxResult таблицу, "обернутую" в панель
                    //с полосами прокрутки
                    hBoxResult.add(new JScrollPane(table));
                    // Перерасположить компоненты в hBoxResult и выполнить
                    //перерисовку
                    hBoxResult.revalidate();
                    // Сделать ряд элементов меню доступными

                    saveToTextMenuItem.setEnabled(true);
                    searchValueMenuItem.setEnabled(true);
                } catch (NumberFormatException ex) {
                    // В случае ошибки преобразования чисел показать сообщение об
                    //ошибке
                    JOptionPane.showMessageDialog(MainFrame.this,
                            "Floating point format error",
                            "Wrong number format", JOptionPane.WARNING_MESSAGE);
                }
            }
        });

        // Создать кнопку "Очистить поля"
        JButton buttonReset = new JButton("Clear fields");
        // Задать действие на нажатие "Очистить поля" и привязать к кнопке
        buttonReset.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent ev) {
                // Установить в полях ввода значения по умолчанию
                textFieldFrom.setText("0.0");
                textFieldTo.setText("1.0");
                textFieldStep.setText("0.1");
                textFieldParam.setText("0.0");
                // Удалить все вложенные элементы контейнера hBoxResult
                hBoxResult.removeAll();
                // Перерисовать сам hBoxResult
                hBoxResult.repaint();
                // Сделать ряд элементов меню недоступными
                saveToTextMenuItem.setEnabled(false);
                searchValueMenuItem.setEnabled(false);
            }
        });

        // Поместить созданные кнопки в контейнер
        Box hboxButtons = Box.createHorizontalBox();
        hboxButtons.setBorder(BorderFactory.createEtchedBorder());
        hboxButtons.add(Box.createHorizontalGlue());
        hboxButtons.add(buttonCalc);
        hboxButtons.add(Box.createHorizontalStrut(30));
        hboxButtons.add(buttonReset);
        hboxButtons.add(Box.createHorizontalGlue());
        // Установить предпочтительный размер области больше минимального, чтобы
        // при компоновке окна область совсем не сдавили
        hboxButtons.setPreferredSize(new Dimension(
                new Double(hboxButtons.getMaximumSize().getWidth()).intValue(),
                new Double(hboxButtons.getMinimumSize().getHeight()*1.5).intValue()));
        // Разместить контейнер с кнопками в нижней (южной) области граничной
//компоновки
        getContentPane().add(hboxButtons, BorderLayout.SOUTH);

        // Область для вывода результата пока что пустая
        hBoxResult = Box.createHorizontalBox();
        // Установить контейнер hBoxResult в главной (центральной) области
//граничной компоновки
        getContentPane().add(hBoxResult);
    }

    protected void saveToTextFile(File selectedFile) {
        try {
            // Создать новый символьный поток вывода, направленный в  указанный файл
            PrintStream out = new PrintStream(selectedFile);

            // Записать в поток вывода заголовочные сведения
            out.println("Function tabulation results:");
            out.println("");
            out.println("Interval from " + data.getFrom() + " before " + data.getTo() +
                    " step " + data.getStep());
            out.println("====================================================");

            // Записать в поток вывода значения в точках
            for (int i = 0; i < data.getRowCount(); i++)
                out.println("Point value " + data.getValueAt(i,0)  + " equally " +
                        data.getValueAt(i,1) + ", integer part of Y is 0: " + data.getValueAt(i, 2));

            // Закрыть поток
            out.close();
        } catch (FileNotFoundException e) {
            // Исключительную ситуацию "ФайлНеНайден" можно не
            // обрабатывать, так как мы файл создаем, а не открываем
        }
    }

    public static void main(String[] args) {
        // Создать экземпляр главного окна
        MainFrame frame = new MainFrame();
        // Задать действие, выполняемое при закрытии окна
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //Показать главное окно приложения
        frame.setVisible(true);
    }
}
