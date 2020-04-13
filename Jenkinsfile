pipeline {
    agent any

    stages {
        stage("Link") {
            steps {
                echo 'Linking...'
                sh 'echo $(pwd)'
                sh 'rm ~/Arduino/libraries/${PWD##*/}'
                sh 'ln -s $(pwd) ~/Arduino/libraries/${PWD##*/}'
            }
        }
    
        stage('Build') {
            steps {
                echo 'Building...'
                sh 'mkdir -p build'
                sh 'mv CircuitOS.ino ${PWD##*/}.ino'
                sh '~/.arduino/arduino-cli compile -b cm:esp32:ringo -o build ${PWD##*/}.ino'
            }
        }
    }
}

