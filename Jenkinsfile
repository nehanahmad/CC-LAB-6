stage('Deploy Backend Containers') {
    steps {
        sh '''
        docker network create app-network || true
        docker rm -f backend1 backend2 || true

        docker run -d \
          --name backend1 \
          --hostname backend1 \
          --network app-network \
          backend-app

        docker run -d \
          --name backend2 \
          --hostname backend2 \
          --network app-network \
          backend-app
        '''
    }
}
