package work;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class prettyGUI {
    private JFrame frame;
    private JTextArea textArea;
    private JTextField inputField;
    private CommandProcessor processor;
    String result;
    public void CreateGUI() {
        processor = new CommandProcessor();
        frame = new JFrame("MAJESTIC_12 // TERMINAL v1.7 // SECURITY CLEARANCE: DELTA");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); //Убивает приложение когда мы его закрываем
        Font monoFont = new Font("Monospaced", Font.PLAIN, 14); //Спавним шрифт
        JPanel panel = new JPanel(new BorderLayout()); //Создаем панель
        textArea = new JTextArea(); //Cоздаем пространство для вывода текста и истории команд
        textArea.setEditable(false); //Запрещаем редактирование чтобы не было вольностей
        textArea.setFont(monoFont); //Применяем шрифт
        textArea.setBackground(Color.BLACK);
        textArea.setForeground(Color.GREEN);
        JScrollPane scrollPane = new JScrollPane(textArea); //Прокрутка для текста
        panel.add(scrollPane, BorderLayout.CENTER); //По центру?
        JPanel inputPanel = new JPanel(new BorderLayout());
        inputPanel.add(new JLabel("> "), BorderLayout.WEST);
        inputField = new JTextField();
        inputField.setFont(monoFont); // Такой же шрифт и для ввода
        inputField.setBackground(Color.BLACK);
        inputField.setForeground(Color.GREEN);
        inputPanel.add(inputField, BorderLayout.CENTER);
        panel.add(inputPanel, BorderLayout.SOUTH);
        frame.add(panel);
        frame.setSize(800, 600);
        frame.setVisible(true);
        inputField.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) { //Если нажали на enter
                String inputText = inputField.getText(); // Получаем введенный текст
                appendText("> " + inputText); // Выводим в текстовую область
                result = processor.process(inputText);
                if (result != null && !result.isEmpty()) {
                    // Разбиваем на строки и добавляем по-строчно, чтобы скролл корректно работал
                    String[] lines = result.split("\\n");
                    for (String line : lines) {
                        appendText(line);
                    }
                }

                inputField.setText(""); // Очищаем поле ввода
            }
        });
    }

    public void appendText(String text) { //Добавить потом медленный вывод для красоты?
        textArea.append(text + "\n");
    }
}


