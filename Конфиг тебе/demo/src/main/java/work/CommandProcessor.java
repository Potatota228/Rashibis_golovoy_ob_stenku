package work;
import work.com.CdCommand;
import work.com.ExitCommand;
import work.com.LsCommand;

public class CommandProcessor {
    public String process(String input) {
        LsCommand ls = new LsCommand();
        CdCommand cd = new CdCommand();
        ExitCommand exit = new ExitCommand();
        
        if (input == null || input.trim().isEmpty()) {
            return "ERROR";
        }
        
        // Обрабатываем переменные окружения
        if (input.contains("$HOME")) {
           input = input.replace("$HOME", "/home/Username");
        }
        if (input.contains("$USER")) {
            input = input.replace("$USER", "Username");
        }
        if (input.contains("$PATH")) {
            input = input.replace("$PATH", "/home/Username/secretDocs/");
        }
        if (input.contains("$SHELL")) {
            input = input.replace("$SHELL", "/bin/bash");
        }

        // Разбираем команды
        String[] parts = input.trim().split("\\s+");
        String command = parts[0];
        
        if (command.equals("ls")) {
            if (parts.length > 1) {
                return ls.main(parts[1]);
            } else {
                return "ERROR: ls command requires an argument";
            }
        }
        if (command.equals("cd")) {
            if (parts.length > 1) {
                return cd.main(parts[1]);
            } else {
                return "ERROR: cd command requires an argument";
            }
        }
        if (command.equals("exit")) {
            exit.exitProgram();
            return "Exiting...";
        }
        
        // Если команда не распознана, но содержит переменные окружения
        if (!command.equals(input.trim())) {
            return input; // Возвращаем обработанную строку с замененными переменными
        }
        
        return "Command not found: " + command;
    }
}