package work;

import java.util.List;

import work.com.CdCommand;
import work.com.ExitCommand;
import work.com.LsCommand;

public class CommandProcessor {
    private List<String> sslist;
    public String process(String input) {
        
        Environment env = new Environment();
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
        //ДАЛЕКО НЕ ФАКТ ЧТО ЭТО РАБОТАЕТ
        String[] parts = input.trim().split("\\s+");
        for (String part : parts){
            if (part.startsWith("//")){
                part.replace(part, "");
            }
        }
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

        if (command.equals("name")) {
            if (parts.length > 1) {
                return env.setUN(parts[1]);
            }
        }

        if (command.equals("--vfs")) {
            if (parts.length > 1 && env.setVFS(parts[1])) {
                return "VFS Path: " + env.getVFS();
            } else {
                return "ERROR: path " + parts[1] + " was not found";
            }
        }

        if (command.equals("--ss")) {
            if (parts.length > 1 && env.ss(parts[1])) {
                this.sslist=env.getSS();
                return "!";
            } else {
                return "ERROR: path " + parts[1] + " was not found";
            }
        }
        if (command.equals("exit")) {
            exit.exitProgram();
            return "Exiting...";

        }

        // // Если команда не распознана, но содержит переменные окружения
        // if (!command.equals(input.trim())) {
        //     return input; // Возвращаем обработанную строку с замененными переменными
        // }

        return "Command " + command + " for " + input + " is not found: ";
    }
    public List<String> getSS(){
        return this.sslist;
    }
}
